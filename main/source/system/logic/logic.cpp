//! @note Missing file header.

//! @note Include <cstddef> (for std::size_t) and <cstdint>.
#include <cstdio>

//! @note Sort headers.
#include "system/logic/logic.h"
#include "driver/serial/interface.h"
#include "driver/gpio/interface.h"
#include "driver/timer/interface.h"
#include "driver/tempsensor/interface.h"
#include "driver/adc/interface.h"
#include "sdkconfig.h"

// P02+ only: keep WiFi/MQTT dependencies out of the original P02 logic build.
#if CONFIG_P02_ENABLE_MQTT
    #include "driver/mqtt/interface.h"
    #include "driver/wifi/interface.h"
#endif // CONFIG_P02_ENABLE_MQTT

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace
{
//! @note Use postfix U for unsigned integers.
constexpr std::uint8_t  LedPin{6};
constexpr std::uint8_t  Tmp36Pin{1};
constexpr std::uint32_t BaudRate{115200};
constexpr std::uint16_t DefaultPeriodMs{500};

#if CONFIG_P02_ENABLE_MQTT
// Values come from menuconfig/sdkconfig so private WiFi data is not hardcoded.
//! @note Very nice utilization of constants!
constexpr const char*   WifiSsid{CONFIG_P02_WIFI_SSID};               // WiFi network used by the ESP32-S3 client.
constexpr const char*   WifiPassword{CONFIG_P02_WIFI_PASSWORD};       // WiFi password used by the ESP32-S3 client.
constexpr const char*   brokerUri{CONFIG_P02_MQTT_BROKER_URI};        // MQTT broker used by the ESP32-S3 client.
constexpr const char*   clientId{CONFIG_P02_MQTT_CLIENT_ID};          // Unique MQTT client ID for this device.
#endif // CONFIG_P02_ENABLE_MQTT

// -----------------------------------------------------------------------------
bool matchStrings(const char* s1, const char* s2) noexcept
{
    //! @note Yoda
    if ((s1 == nullptr) || (s2 == nullptr)) { return false; }

    //! @note Initialize with {} or {0U}.
    std::size_t i{0};

    while (true)
    {
        if (s1[i] != s2[i]) { return false; }
        if (s1[i] == '\0')  { break; }
        i++;
    }
    return true;
}

// -----------------------------------------------------------------------------
bool startsWith(const char* text, const char* prefix) noexcept
{
    //! @note Use Yoda notation.
    if ((text == nullptr) || (prefix == nullptr)) { return false; }

    //! @note Initialize with {} or {0U}.
    std::size_t i{0};

    while (prefix[i] != '\0')
    {
        if (text[i] != prefix[i]) { return false; }
        i++;
    }
    return true;
}

// -----------------------------------------------------------------------------
std::uint32_t parseUint32(const char* text) noexcept
{
    //! @note Yoda again.
    if (text == nullptr) { return 0U; }
    std::uint32_t value{0U};

    //! @note Initialize with {} or {0U}.
    for (std::size_t i{0}; text[i] != '\0'; i++)
    {
        if ((text[i] < '0') || (text[i] > '9')) 
        {
            return 0U;
        }
        value = (value * 10U) + static_cast<std::uint32_t>(text[i] - '0');
    }
    return value;
}
} // namespace 

namespace app::logic
{
//! @note Nice! Note that you must define the destructor here if the driver timers from the factory
//!       aren't included directly in the header. If they are, I would advise you to place this
//!       definition in the header instead.
// -----------------------------------------------------------------------------
Logic::~Logic() noexcept = default;

// -----------------------------------------------------------------------------
Logic::Logic(driver::factory::Interface& factory) noexcept
    : mySerial{factory.serial(BaudRate)}
    , myLed{factory.gpioOutput(LedPin)}
    , myTimer{factory.timer(DefaultPeriodMs)}
    , myAdc{factory.adc(Tmp36Pin)}
    , myTempSensor{factory.tempSensor(Tmp36Pin, *myAdc)}
#if CONFIG_P02_ENABLE_MQTT
    , myWifi{factory.wifi(WifiSsid, WifiPassword)}
    , myMqtt{factory.mqtt(brokerUri, clientId)}
#endif // CONFIG_P02_ENABLE_MQTT
{
    setStartState();
    initializeDrivers();
}

// -----------------------------------------------------------------------------
void Logic::setStartState() noexcept
{
    myBlinkEnabled = false;
    myPeriodMs     = DefaultPeriodMs;
    
    if (myLed) { myLed->write(false); }

    if (myTimer)
    {
        myTimer->setPeriod(myPeriodMs);
        myTimer->stop();
    }
}

// -----------------------------------------------------------------------------
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

#if CONFIG_P02_ENABLE_MQTT
    // P02+ mode: networking must be ready before MQTT can connect.
    if (myWifi && !myWifi->isConnected())
    {
        myWifi->connect();
    }
    if (myMqtt && myWifi && myWifi->isConnected() && !myMqtt->isConnected())
    {
        myMqtt->connect();
    }
#endif // CONFIG_P02_ENABLE_MQTT
}

// -----------------------------------------------------------------------------
void Logic::processSerial() noexcept
{
    if (!mySerial) return;

    //! @note Avoid magic numbers: use a constexpr and assign 16U.
    char commandBuf[16]{};

    //! @note You can use auto here.
    std::uint16_t bytesRead = mySerial->read(commandBuf, sizeof(commandBuf));

    //! @note Yoda notation, and it should be 0U; 0U is fine, even if it's technically a magic number.
    if (bytesRead > 0)
    {
        handleCommand(commandBuf);
    }
}

// -----------------------------------------------------------------------------
#if CONFIG_P02_ENABLE_MQTT
void Logic::processMqtt() noexcept
{
    if (!myMqtt) { return; }

    if (myWifi && !myWifi->isConnected())
    {
        myMqttSubscribed = false;
        myWifi->reconnect();
        return;
    }

    if (!myMqtt->isConnected())
    {
        myMqttSubscribed = false;
        myMqtt->connect();
        return;
    }

    if (!myMqttSubscribed)
    {
        myMqttSubscribed = myMqtt->subscribe("p02/command");
    }

    myMqtt->loop();

    //! @note Magic numbers.
    char topic[32]{};
    char payload[32]{};

    if (myMqtt->readMessage(topic, sizeof(topic), payload, sizeof(payload)))
    {
        handleCommand(payload);
    }
}
#endif // CONFIG_P02_ENABLE_MQTT

// -----------------------------------------------------------------------------
void Logic::handleCommand(const char* command) noexcept
{
    //! @note Yoda.
    if (!myLed || !myTimer || (command == nullptr)) { return; }

    // Strip trailing \r (CRLF terminals send \r\n; \n is already consumed by read()).
    //! @note Magic number.
    char buf[16]{};

    //! Initialize with {} or {0U}.
    std::size_t i{0};
    while (command[i] != '\0' && command[i] != '\r' && i < (sizeof(buf) - 1U))
    {
        buf[i] = command[i];
        i++;
    }
    buf[i] = '\0';
    command = buf;

    //! @note Nice function matchStrings(), looks much nicer than std::strcmp().
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
        //! @note Magic number.
        const char* valueText = command + 7;
        const std::uint32_t newPeriod = parseUint32(valueText);

        //! @note Yoda.
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

// -----------------------------------------------------------------------------
void Logic::processTimer() noexcept
{
    if (myBlinkEnabled && myLed && myTimer && myTimer->isTimeout())
    {
        myLed->toggle();
    }
}

// -----------------------------------------------------------------------------
void Logic::printStatus() noexcept
{
    if (!myTempSensor) { return; }

    //! @note Feel free to use auto here.
    const float temp = myTempSensor->readCelsius();

    //! @note Magic number.
    char buffer[64]{};

    std::snprintf(buffer, sizeof(buffer), "Status:\nBlink = %s\nPeriod = %lu ms\nTemp = %.1f C\n",
        myBlinkEnabled ? "On" : "Off", static_cast<unsigned long>(myPeriodMs),
        static_cast<double>(temp));

    if (mySerial)
    {
        mySerial->write(buffer);
    }

#if CONFIG_P02_ENABLE_MQTT
    if (myMqtt && myMqtt->isConnected())
    {
        myMqtt->publish("p02/status", buffer);
    }
#endif // CONFIG_P02_ENABLE_MQTT
}

// -----------------------------------------------------------------------------
void Logic::printTemperature() noexcept
{
    if (!mySerial || !myTempSensor) { return; }

    //! @note auto or just brace initialization.
    const float temp = myTempSensor->readCelsius();

    //! @note Magic again.
    char buffer[24]{};

    std::snprintf(buffer, sizeof(buffer), "Temp = %.1f C\n", static_cast<double>(temp));
    mySerial->write(buffer);
}

// -----------------------------------------------------------------------------
void Logic::run(const std::atomic<bool>& stop) noexcept
{
    while(!stop.load())
    {
        processSerial();

#if CONFIG_P02_ENABLE_MQTT
        processMqtt();
#endif // CONFIG_P02_ENABLE_MQTT

        processTimer();
        //! @note Magic number.
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
} // namespace app::logic
