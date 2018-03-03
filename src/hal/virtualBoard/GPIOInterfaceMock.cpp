#include "../include/GPIOInterface.h"

using namespace hardware;
using namespace std;

GPIOInterface::GPIOInterface(GPIO gpio)
    : gpio_(gpio)
{}

GPIOInterface::~GPIOInterface()
{}

void GPIOInterface::activateInterrupt(std::function< void() >  callback)
{
    callback_ = callback;
}

GPIOState GPIOInterface::getState()
{
    return gpio_.state;
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


}