#include "../include/Switch.h"

#include <iostream>

using namespace std;
using namespace hardware;

Switch::Switch(GPIO gpio)
        : GPIOInterface(gpio)
{
}

Switch::~Switch()
{

}

bool Switch::registerHandler(/*gpioISRFuncEx_t fun, */const int &edge, const int &timeout, void *intData)
{

    return true;
}
