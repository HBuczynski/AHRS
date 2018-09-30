#include "../include/Switch.h"

using namespace std;
using namespace hardware;

Switch::Switch(GPIO gpio)
    : GPIOInterface(gpio)
{
}

Switch::~Switch()
{

}

bool Switch::registerHandler(gpioISRFuncEx_t fun, const int &edge, const int &timeout = 0, void *intData = nullptr)
{
    if(!gpioSetISRFuncEx(gpio_.pinNumber, edge, timeout,interruptHandler, intData))
    {
        std::cout << "ISR register correct." << std::endl;
        return true;
    }
    return false;
}