#ifndef AHRS_SWITCHHANDLE_H
#define AHRS_SWITCHHANDLE_H

#include <hal/include/GPIOInterface.h>
#include <hal/include/Switch.h>
#include <functional>

namespace  peripherals
{
    enum class SwitchCode : uint8_t
    {
        FIRST_SWITCH = 0x01,
        SECOND_SWITCH = 0x02,
        THIRD_SWITCH = 0x03,
        FOURTH_SWITCH = 0x04
    };

    enum class SwitchState : uint8_t
    {
        LOW_DEBOUNCE_SECTION = 0x01,
        LOW_STATE = 0x02,
        HIGH_DEBOUNCE_SECTION = 0x03,
        HIGH_STATE = 0x04,
        ERROR_CRITICAL_TIME = 0x05,
        ERROR_DEBOUNCE = 0x06,
    };

    class SwitchHandle
    {
    public:
        SwitchHandle() {};
        virtual ~SwitchHandle() {};

        virtual void resetSwitch() = 0;
        virtual void initializeCallbacks(std::function< void() > pressedSwitchCallback, std::function< void(SwitchCode, SwitchState) > errorCallback) = 0;
    };
}

#endif //AHRS_SWITCHHANDLE_H
