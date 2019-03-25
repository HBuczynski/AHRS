#include "../include/Switch.h"

#include <iostream>

using namespace std;
using namespace hardware;

Switch::Switch(GPIO gpio)
        : GPIOInterface(gpio),
          isListening_(false),
          internalData_(nullptr),
          edge_(0)
{
    dictionary_.insert({71, 14});
    dictionary_.insert({77, 15});
    dictionary_.insert({65, 18});
    dictionary_.insert({72, 23});
}

Switch::~Switch()
{
    isListening_ = false;

    if(listeningThread_.joinable())
    {
        listeningThread_.join();
    }
}

bool Switch::registerHandler(gpioISRFuncEx_t fun, const int &edge, const int &timeout, void *intData)
{
    callback_ = fun;
    edge_ = edge;
    internalData_ = intData;

    if(isListening_ == false)
    {
        isListening_ = true;
        listeningThread_ = thread(&Switch::listenKeys, this);
    }

    return true;
}

void Switch::listenKeys()
{
    while(isListening_)
    {
        const int input = cin.get();
        const auto dictionaryElement = dictionary_.find(input);

        if(dictionaryElement == dictionary_.end())
            continue;

        if ( (*dictionaryElement).second == gpio_.pinNumber )
        {
            callback_(gpio_.pinNumber, FALLING_EDGE, 0, internalData_);
            this_thread::sleep_for(chrono::milliseconds(30));
            callback_(gpio_.pinNumber, RISING_EDGE, 0, internalData_);
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}