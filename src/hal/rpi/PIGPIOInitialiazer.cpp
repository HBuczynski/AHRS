#include "../include/PIGPIOInitializer.h"
#include "../../../3rd_party/PIGPIO/pigpio.h"

#include <iostream>

using namespace std;
using namespace hardware;

atomic<bool> PIGPIOInitializer::initializerFlag_ (false);

PIGPIOInitializer::PIGPIOInitializer()
{}

PIGPIOInitializer::~PIGPIOInitializer()
{}

void PIGPIOInitializer::initialize()
{
    if(!initializerFlag_)
    {
        gpioCfgSocketPort(9500);
        gpioCfgInterfaces(PI_DISABLE_SOCK_IF);

        gpioInitialise();

        initializerFlag_ = true;
    }
}