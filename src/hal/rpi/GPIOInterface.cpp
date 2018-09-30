#include "../include/GPIOInterface.h"
#include <system_error>
#include "../../../3rd_party/PIGPIO/pigpio.h"

#include "../include/PIGPIOInitializer.h"

using namespace hardware;
using namespace std;

GPIOInterface::GPIOInterface(GPIO gpio)
        : gpio_(gpio)
{
    PIGPIOInitializer::initialize();

    initialize();
}

GPIOInterface::~GPIOInterface()
{}


bool GPIOInterface::initialize() const
{
    if(!gpioSetMode(gpio_.pinNumber, getMode(gpio_.pinMode)) && !gpioSetPullUpDown(gpio_.pinNumber, gpio_.pushPullMode))
    {
        return true;
    }

    return false;
}

uint8_t GPIOInterface::getMode(GPIOMode mode)
{
    uint8_t mode = 0;

    if(gpio_.pinMode == GPIOMode::IN)
    {
        mode = PI_INPUT;
    }
    else
    {
        mode = PI_OUTPUT;
    }

    return mode;
}

uint8_t GPIOInterface::getPullMode(GPIOPullMode pullMode)
{
    uint8_t pullMode = 0;

    if(gpio_.pushPullMode == GPIOPullMode::DOWN)
    {
        pullMode = PI_PUD_DOWN;
    }
    else
    {
        pullMode = PI_PUD_UP;
    }

    return pullMode;
}

void GPIOInterface::pinWrite(int state)
{
    gpioWrite(gpio_.pinNumber, state);
}

int GPIOInterface::pinRead() const
{
    return gpioRead(gpio_.pinNumber);
}

void GPIOInterface::activateRaisingInterrupt(std::function<void()> callback)
{
    raisingInterruptCallback_ = callback;


}

void GPIOInterface::activateFallingInterrupt(std::function<void()> callback)
{
    fallingInterruptCallback_ = callback;

    //TODO
}
