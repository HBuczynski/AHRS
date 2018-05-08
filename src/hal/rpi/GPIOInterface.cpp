#include "../include/GPIOInterface.h"
#include <system_error>
#include <../../3rd_party/PIGPIO/pigpio.h>


using namespace hardware;
using namespace std;

GPIOInterface::GPIOInterface(GPIO gpio)
        : gpio_(gpio)
{
    initialize();
}

GPIOInterface::~GPIOInterface()
{}


bool GPIOInterface::initialize() const
{
    if(!gpioSetMode(pinNumber, pinMode) && !gpioSetPullUpDown(pinNumber, pushPullMode))
    {
        return true;
    }

    return false;
}

void GPIOInterface::pinWrite(int state)
{

}

int GPIOInterface::pinRead() const
{

}

void GPIOInterface::activateRaisingInterrupt(std::function<void()> callback)
{
    raisingInterruptCallback_ = callback;
}

void GPIOInterface::activateFallingInterrupt(std::function<void()> callback)
{
    fallingInterruptCallback_ = callback;
}

void GPIOInterface::activateInterrupt(std::function< void() >  callback)
{
    callback_ = callback;

    std::function< void() > callback = std::bind(&GPIOInterface::interruptHandler, this);
    if(gpio_.interrupt == InterruptEdge::RISING)
    {
        if (wiringPiISR(gpio_.pinNumber, INT_EDGE_RISING, callback.target()) < 0)
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

