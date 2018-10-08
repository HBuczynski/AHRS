#include "../include/PIGPIOInitializer.h"

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
    cout << initializerFlag_ << endl;

    if(!initializerFlag_)
    {
    }
}

void PIGPIOInitializer::terminate()
{
    if(initializerFlag_)
    {
        initializerFlag_ = false;
    }
}