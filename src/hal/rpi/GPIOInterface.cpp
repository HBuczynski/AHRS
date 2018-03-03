#include "../include/GPIOInterface.h"
#include <system_error>

using namespace hardware;
using namespace std;

GPIOInterface::GPIOInterface(GPIO gpio)
        : gpio_(gpio)
{
    initialize();
}

GPIOInterface::~GPIOInterface()
{}

void GPIOInterface::initialize()
{
    if( wiringPiSetup() == -1)
    {
        throw system_error(EDOM, generic_category(), "There is problem with wiringPi library.");
    }

    if(gpio_.mode == GPIOMode::INPUT)
    {
        pinMode(gpio_.mode, INPUT);
    }
    else if(gpio_.mode == GPIOMode::OUTPUT)
    {
        pinMode(gpio_.mode, OUTPUT);
    }
}

void GPIOInterface::activateInterrupt(std::function< void() >  callback)
{
    callback_ = callback;

    if(gpio_.interrupt == InterruptEdge::RISING)
    {
        if (wiringPiISR(gpio_.pinNumber, INT_EDGE_RISING, &interruptHandler) < 0)
        {
            throw system_error(EDOM, generic_category(), "There is problem with setting interrupt.");
        }
    }
    else if(gpio_.interrupt == InterruptEdge::FALLING)
    {
        if (wiringPiISR(gpio_.pinNumber, INT_EDGE_FALLING, &interruptHandler) < 0)
        {
            throw system_error(EDOM, generic_category(), "There is problem with setting interrupt.");
        }
    }
    else if(gpio_.interrupt == InterruptEdge::BOTH)
    {
        if (wiringPiISR(gpio_.pinNumber, INT_EDGE_BOTH, &interruptHandler) < 0)
        {
            throw system_error(EDOM, generic_category(), "There is problem with setting interrupt.");
        }
    }
}

GPIOState GPIOInterface::getState()
{
    if(digitalRead(gpio_.pinNumber))
    {
        return GPIOState::HIGH;
    }
    else
    {
        return GPIOState::LOW;
    }
}

uint8_t GPIOInterface::getPinNumber()
{
    return gpio_.pinNumber;
}

GPIOMode GPIOInterface::getMode()
{
    return gpio_.mode;
}

void GPIOInterface::interruptHandler()
{
    callback_();
}