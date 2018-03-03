#ifndef AHRS_SWITCHESHANDLE_H
#define AHRS_SWITCHESHANDLE_H

#include <hal/include/GPIOInterface.h>
#include <chrono>

namespace  peripherals
{
    // Class is responsible for handle one of the button.
    class SwitchesHandle
    {
    public:
        SwitchesHandle(hardware::GPIO gpioProperties);
        ~SwitchesHandle();

    private:
        void handleInterrupt();

    private:
        const std::string switchName_;
        hardware::GPIOInterface gpio_;

        const uint8_t CRITICAL_TIME = 4;
    };
}

#endif