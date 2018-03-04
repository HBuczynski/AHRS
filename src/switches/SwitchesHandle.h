#ifndef AHRS_SWITCHESHANDLE_H
#define AHRS_SWITCHESHANDLE_H

#include <hal/include/GPIOInterface.h>
#include <chrono>

namespace  peripherals
{
    typedef std::chrono::steady_clock::time_point TimePoint;

    // Class is responsible for handle one of the button.
    class SwitchesHandle
    {
    public:
        SwitchesHandle(hardware::GPIO gpioProperties);
        ~SwitchesHandle();

    private:
        void handleInterrupt();

    private:
        hardware::GPIOInterface gpio_;
        TimePoint lastInterrupt;

        const uint16_t CRITICAL_TIME = 4000;
        const uint16_t DEBOUNCE_TIME = 200;
    };
}

#endif