#include "SwitchesHandle.h"
#include <thread>
#include <system_error>

using namespace std;
using namespace hardware;
using namespace peripherals;


SwitchesHandle::SwitchesHandle(hardware::GPIO gpioProperties)
    : gpio_(gpioProperties)
{
    std::function< void() > callback = bind(&SwitchesHandle::handleInterrupt, this);

    gpio_.activateInterrupt(callback);
    lastInterrupt = chrono::steady_clock::now();
}

SwitchesHandle::~SwitchesHandle()
{}

void SwitchesHandle::handleInterrupt()
{
    const auto currentTimeInterrupt = chrono::steady_clock::now();

    if(chrono::duration_cast<chrono::milliseconds>(currentTimeInterrupt - lastInterrupt).count() > DEBOUNCE_TIME)
    {
        // ogarnąc inaczej !!! zbocze narastajace i opadajace - timer to kontroluje
        // dwa przyciski tez sprawdzic !!!
        // Check whether button does not have any mechanical failure.
        while (gpio_.getState() == GPIOState::HIGH)
        {
            const auto end = chrono::steady_clock::now();

            if (chrono::duration_cast<chrono::milliseconds>(end - currentTimeInterrupt).count() > CRITICAL_TIME)
            {
                throw system_error(EDOM, generic_category(), "Buttons was pushed too long.");
            }
        }

        // do notification to ui
        // run signal

    }

    lastInterrupt = currentTimeInterrupt;
}