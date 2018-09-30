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

bool Switch::registerHandler(const int &edge, const int &timeout, void *intData)
{

    return true;
}

void Switch::callback(int gpio, int level, uint32_t tick, void *userdata)
{
    cout << "GPIO: " << gpio << endl;
    cout << "Level: " << level << endl;
}