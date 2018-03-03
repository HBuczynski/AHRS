#include "SwitchesHandle.h"
#include <thread>
#include <system_error>

using namespace std;
using namespace hardware;
using namespace peripherals;


SwitchesHandle::SwitchesHandle(hardware::GPIO gpioProperties)
    : gpio_(gpioProperties)
{
    std::function< void() > callback = std::bind(&SwitchesHandle::handleInterrupt, this);
    gpio_.activateInterrupt(callback);
}

SwitchesHandle::~SwitchesHandle()
{}

void SwitchesHandle::handleInterrupt()
{
    this_thread::sleep_for(std::chrono::milliseconds(10));

    if( gpio_.getState() == GPIOState::HIGH)
    {
        // do notification to ui
        // run signal
    }

    const auto start = std::chrono::steady_clock::now();

    while(gpio_.getState() == GPIOState::HIGH)
    {
        const auto end = std::chrono::steady_clock::now();

        if(std::chrono::duration_cast<std::chrono::seconds>(end - start).count() > CRITICAL_TIME)
        {
            throw system_error(EDOM, generic_category(), "Buttons was pushed too long.");
        }
    }
}

