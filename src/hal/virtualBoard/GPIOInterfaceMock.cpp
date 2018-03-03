#include "../include/GPIOInterface.h"

using namespace hardware;
using namespace std;

GPIOInterface::GPIOInterface(uint8_t pinNumber, GPIOMode mode)
    : pinNumber_(pinNumber),
      mode_(mode)
{

}

GPIOInterface::~GPIOInterface()
{

}

void GPIOInterface::activateInterrupt(std::function< void() >  callback, InterruptEdge edge)
{

}

GPIOState GPIOInterface::getState()
{
    return state_;
}

uint8_t GPIOInterface::getPinNumber()
{
    return pinNumber_;
}

GPIOMode GPIOInterface::getMode()
{
    return mode_;
}

void GPIOInterface::interruptHandler()
{


}