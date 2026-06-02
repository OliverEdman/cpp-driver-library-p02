#include "system/logic/logic.h"
#include "driver/serial/interface.h"
#include "driver/gpio/interface.h"
#include "driver/timer/interface.h"
#include "driver/tempsensor/interface.h"
#include "driver/adc/interface.h"

#include <cstdio>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace
{
    constexpr std::uint8_t  LedPin{6};
    constexpr std::uint8_t  Tmp36Pin{1};
    constexpr std::uint32_t BaudRate{115200};
    constexpr std::uint16_t DefaultPeriodMs{500};

    bool matchStrings(const char* s1, const char* s2) noexcept
    {
        if ((s1 == nullptr) || (s2 == nullptr)) { return false; }

        std::size_t i{0};
        while (true)
        {
            if (s1[i] != s2[i]) { return false; }
            if (s1[i] == '\0')  { break; }
            i++;
        }
        return true;
    }
    
    bool startsWith(const char* text, const char* prefix) noexcept
    {
    if ((text == nullptr) || (prefix == nullptr)) { return false; }

    std::size_t i{0};
    while (prefix[i] != '\0')
    {
        if (text[i] != prefix[i]) { return false; }
        i++;
    }

    return true;
    }

    std::uint32_t parseUint32(const char* text) noexcept
{
    if (text == nullptr) { return 0U; }

    std::uint32_t value{0U};

    for (std::size_t i{0}; text[i] != '\0'; i++)
    {
        if ((text[i] < '0') || (text[i] > '9')) {
            return 0U;
        }

        value = (value * 10U) + static_cast<std::uint32_t>(text[i] - '0');
    }

    return value;
}
    
} // namespace 



namespace app::logic
{

Logic::~Logic() noexcept = default;

Logic::Logic(driver::factory::Interface& factory) noexcept
    :mySerial{factory.serial(BaudRate)}
    ,myLed{factory.gpioOutput(LedPin)}
    ,myTimer{factory.timer(DefaultPeriodMs)}
    ,myAdc{factory.adc(Tmp36Pin)}
    ,myTempSensor{factory.tempSensor(Tmp36Pin, *myAdc)}
    {
        setStartState();
        initializeDrivers();
    }

void Logic::setStartState() noexcept
{
    myBlinkEnabled = false;
    myPeriodMs     = DefaultPeriodMs;
    

    if (myLed) {myLed->write(false); }

    if (myTimer)
    {
        myTimer->setPeriod(myPeriodMs);
        myTimer->stop();
    }
}

void Logic::initializeDrivers() noexcept
{
    if (myAdc && !myAdc->isInitialized())
    {
    myAdc->init();
    }
    if (mySerial && !mySerial->isInitialized())
    {
    mySerial->connect();
    }
}

void Logic::processSerial() noexcept
{
    if (!mySerial) return;

    char commandBuf[16]{};


    std::uint16_t bytesRead = mySerial->read(commandBuf, sizeof(commandBuf));

    if (bytesRead > 0)
    {
        handleCommand(commandBuf);
    }
}


void Logic::handleCommand(const char* command) noexcept
{
    if (!myLed || !myTimer || (command == nullptr)) return;

    // Strip trailing \r (CRLF terminals send \r\n; \n is already consumed by read()).
    char buf[16]{};
    std::size_t i{0};
    while (command[i] != '\0' && command[i] != '\r' && i < (sizeof(buf) - 1U))
    {
        buf[i] = command[i];
        i++;
    }
    buf[i] = '\0';
    command = buf;

    if (matchStrings(command, "on")) 
    {
        myBlinkEnabled = false;
        myTimer->stop();
        myLed->write(true);
    }
    else if (matchStrings(command, "off")) 
    {
        myBlinkEnabled = false;
        myTimer->stop();
        myLed->write(false);
    }
    else if (matchStrings(command, "blink on")) 
    {
        myBlinkEnabled = true;
        myTimer->setPeriod(myPeriodMs);
        myTimer->start();
    }
    else if (matchStrings(command, "blink off")) 
    {
        myBlinkEnabled = false;
        myTimer->stop();
        myLed->write(false);
    }
    else if (matchStrings(command, "status")) 
    {
        printStatus();
    }
    else if (matchStrings(command, "temp")) 
    {
        printTemperature();
    }
    else if (startsWith(command, "period "))
    {
    const char* valueText = command + 7; 
    const std::uint32_t newPeriod = parseUint32(valueText);

    if (newPeriod > 0U)
    {
        myPeriodMs = newPeriod;
        myTimer->setPeriod(myPeriodMs);

        if (myBlinkEnabled)
        {
            myTimer->start();
        }
        if (mySerial)
            {
            mySerial->write("Period updated\n");
            }
        }
        else
        {
            if (mySerial)
            {
            mySerial->write("Invalid period\n");
            }
        }
}
}

void Logic::processTimer() noexcept
{
    if (myBlinkEnabled && myLed && myTimer && myTimer->isTimeout())
    {
    myLed->toggle();
    }
}


void Logic::printStatus() noexcept
{
    if (!mySerial || !myTempSensor) {
        return;
    }

    const float temp = myTempSensor->readCelsius();

    char buffer[64]{};

    std::snprintf(
        buffer,
        sizeof(buffer),
        "Status:\nBlink = %s\nPeriod = %lu ms\nTemp = %.1f C\n",
        myBlinkEnabled ? "On" : "Off",
        static_cast<unsigned long>(myPeriodMs),
        static_cast<double>(temp)
    );

    mySerial->write(buffer);
}

void Logic::printTemperature() noexcept
{
    if(!mySerial || !myTempSensor) { return; }


    const float temp = myTempSensor->readCelsius();

    char buffer[24]{};

    std::snprintf(
        buffer,
        sizeof(buffer),
        "Temp = %.1f C\n",
        static_cast<double>(temp)
    );

    mySerial->write(buffer);
}




void Logic::run(const std::atomic<bool>& stop) noexcept
{
    while(!stop.load())
    {
        processSerial();
        processTimer();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


} // namespace app::logic
