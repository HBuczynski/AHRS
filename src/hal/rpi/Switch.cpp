#include "../include/Switch.h"

#include <iostream>

using namespace std;
using namespace hardware;

Switch::Switch(GPIO gpio)
    : GPIOInterface(gpio)
{
}

Switch::~Switch()
{}

bool Switch::registerHandler(/*gpioISRFuncEx_t fun, */const int &edge, const int &timeout, void *intData)
{
    if(!gpioSetISRFuncEx(gpio_.pinNumber, edge, timeout, callback, intData))
    {
        std::cout << "ISR register correct." << std::endl;
        return true;
    }
    return false;
}

void Switch::callback(int gpio, int level, uint32_t tick, void *userdata)
{
    cout << "Level: " << level << endl;
}