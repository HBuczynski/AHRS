#ifndef AHRS_SWITCHESHANDLE_H
#define AHRS_SWITCHESHANDLE_H

#include <hal/include/GPIOInterface.h>
#include <chrono>

namespace  peripherals
{
    enum SwitchesCode : uint8_t
    {
        UP_SWITCH = 0x10,
        BOTTOM_SWITCH = 0x20,
        OK_SWITCH = 0x30,
        CANCEL_SWITCH = 0x40
    };

    enum SwitchState : uint8_t
    {
        HIGH_BEFORE_DEBOUNCE,
        HIGH_AFTER_DEBONCE,
        LOW_STATE,
        ERROR_STATE
    };

    // Class is responsible for handle one of the button.
    class SwitcheHandle
    {
    public:
        SwitcheHandle(hardware::GPIO gpioProperties, SwitchesCode code);
        ~SwitcheHandle();

        void resetSwitch();
        void initializeCallbacks(std::function< void(SwitchesCode) > pressedSwitchCallback, std::function< void(SwitchesCode) > errorCallback);

    private:
        void handleFallingInterrupt();
        void handleRaisingInterrupt();

        void initializeDebounceTimer();
        void changeStateAfterDebounce(int);

        void initializeCriticalDelay();
        void changeOnDelayState(int);

        void checkErrorInterruptCounter();

    private:
        hardware::GPIOInterface gpio_;
        SwitchesCode code_;
        SwitchState  state_;

        uint8_t errorInterruptCounter_;
        std::function< void(SwitchesCode) > pressedSwitchCallback_;
        std::function< void(SwitchesCode) > errorCallback_;

        const uint16_t CRITICAL_TIME_SEC = 4;
        const uint32_t DEBOUNCE_TIME_MICRO_SEC = 100000;
    };
}

#endif