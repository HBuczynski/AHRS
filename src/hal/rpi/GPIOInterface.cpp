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
    if(!gpioSetMode(gpio_.pinNumber, gpio_.pinMode) && !gpioSetPullUpDown(gpio_.pinNumber, gpio_.pushPullMode))
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

    //TODO
}

void GPIOInterface::activateFallingInterrupt(std::function<void()> callback)
{
    fallingInterruptCallback_ = callback;

    //TODO
}
