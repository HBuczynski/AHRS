#include "../include/GPIOInterface.h"

using namespace hardware;
using namespace std;

GPIOInterface::GPIOInterface(GPIO gpio)
    : gpio_(gpio)
{}

GPIOInterface::~GPIOInterface()
{}

void GPIOInterface::activateRaisingInterrupt(std::function<void()> callback)
{
    raisingInterruptCallback_ = callback;
}

void GPIOInterface::activateFallingInterrupt(std::function<void()> callback)
{
    fallingInterruptCallback_ = callback;
}

bool GPIOInterface::initialize() const
{
    return true;
}

void GPIOInterface::pinWrite(int state)
{

}

int GPIOInterface::pinRead() const
{
    return 0;
}