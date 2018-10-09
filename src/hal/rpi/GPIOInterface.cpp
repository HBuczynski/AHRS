#include "../include/GPIOInterface.h"
#include <system_error>
#include <iostream>

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
    if(!gpioSetMode(gpio_.pinNumber, getMode(gpio_.pinMode)) && !gpioSetPullUpDown(gpio_.pinNumber, getPullMode(gpio_.pushPullMode)))
    {
        return true;
    }

    return false;
}

uint8_t GPIOInterface::getMode(GPIOMode mode) const
{
    uint8_t currentMode = 0;

    if(mode == GPIOMode::IN)
    {
        currentMode = PI_INPUT;
    }
    else
    {
        currentMode = PI_OUTPUT;
    }

    return currentMode;
}

uint8_t GPIOInterface::getPullMode(GPIOPullMode pullMode) const
{
    uint8_t currentPullMode = 0;

    if(pullMode == GPIOPullMode::DOWN)
    {
        currentPullMode = PI_PUD_DOWN;
    }
    else
    {
        currentPullMode = PI_PUD_UP;
    }

    return currentPullMode;
}

void GPIOInterface::pinWrite(int state)
{
    gpioWrite(gpio_.pinNumber, state);
}

int GPIOInterface::pinRead() const
{
    return gpioRead(gpio_.pinNumber);
}