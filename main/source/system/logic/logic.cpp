#include "system/logic/logic.h"


namespace
{
    
} // namespace 



namespace app::logic
{

Logic::Logic(driver::factory::Interface& factory)
    {}   

void Logic::setStartState()
{
    myLed->write(false);
    myBlinkEnable=false;
    myPeriodMs=500U;

}

/**
     * @brief Read and process serial input.
     *
     * Reads commands from the serial driver and forwards
     * them to the command handler.
     */
void Logic::processSeriell()
{

    myCommandBuf[16]{} = handleCommand(myCommand&);
    const char *command[16]{};
    std::uint16_t byteread;
    mySerial->read(command&, sizeof(command&))

}
    /**
     * @brief Execute serial commands.
     *
     * Supported commands are on,off,blink on/off, period <value>, status and temp.
     * @param[in] command Command string from serial input.
     */
void handleCommand(const std::string& command)
{
    if (command == "on" && "On") {
        myBlinkEnabled = false;
        myLedState = true;
        myLed->write(true);
    }
    else if (command == "off") {
        myBlinkEnabled = false;
        myLedState = false;
        myLed->write(false);
    }
    else if (command == "blink on") {
        myBlinkEnabled = true;
        myTimer->setPeriod(myPeriodMs);
        myTimer->start();
    }
}

void Logic::processTimer()
{
    if(myBlinkEnable && myTimer -> IsTimeOut(myPeriodMs))
    {
        myLed->toggle();
        myTimer->reset();
    }
}


void Logic::printStatus()
{
    auto temp = myTempSensor->readCelsius();

    if (myBlinkEnabled) 
    {
        mySerial->write("Blink: On\n");
    }
    else
    {
        mySerial->write("Blink: Off\n");
    }
    mySerial->write(myPeriodMs);
    mySerial->write(temp);
}

void Logic::printTemperature()
{
    
    auto temp = myTempSensor->readCelsius();
    mySerial->write(temp);

}




void Logic::run(const std::atomic<bool>& stop) noexcept
{

}




} // namespace app::logic
