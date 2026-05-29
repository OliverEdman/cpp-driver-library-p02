#include "system/logic/logic.h"
#include "driver/serial/interface.h"
#include "driver/gpio/interface.h"
#include "driver/timer/interface.h"
#include "driver/tempsensor/interface.h"
#include "driver/adc/interface.h"

#include <cstdio>

namespace
{
    constexpr std::uint8_t  LedPin{6};
    constexpr std::uint8_t  Tmp36Pin{1};
    constexpr std::uint32_t BaudRate{9600};
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

Logic::Logic(driver::factory::Interface& factory)
    :mySerial{factory.serial(BaudRate)}
    ,myLed{factory.gpioOutput(LedPin)}
    ,myTimer{factory.timer(DefaultPeriodMs)}
    ,myAdc{factory.adc(Tmp36Pin)}
    ,myTempSensor{factory.tempSensor(Tmp36Pin, *myAdc)}
    {
        setStartState();
    }

void Logic::setStartState()
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

/**
     * @brief Read and process serial input.
     *
     * Reads commands from the serial driver and forwards
     * them to the command handler.
     */
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

    /**
     * @brief Execute serial commands.
     *
     * Supported commands are on,off,blink on/off, period <value>, status and temp.
     * @param[in] command Command string from serial input.
     */
void Logic::handleCommand(const char* command) noexcept
{
    if (!myLed || !myTimer || (command == nullptr)) return;

    if (matchStrings(command, "on") || matchStrings(command, "On")) 
    {
        myBlinkEnabled = false;
        myLed->write(true);
    }
    else if (matchStrings(command, "off")) 
    {
        myBlinkEnabled = false;
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

void Logic::processTimer()
{
    if (myBlinkEnabled && myLed && myTimer && myTimer->isTimeout())
{
    myLed->toggle();
    myTimer->reset();
}
}


void Logic::printStatus()
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

void Logic::printTemperature()
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

}




} // namespace app::logic
