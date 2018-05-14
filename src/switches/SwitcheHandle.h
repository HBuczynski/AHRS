#ifndef AHRS_SWITCHESHANDLE_H
#define AHRS_SWITCHESHANDLE_H

#include <logger/Logger.h>
#include <hal/include/GPIOInterface.h>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <string>
#include <cstring>
#include <csignal>

#include <bits/siginfo.h>

namespace  peripherals
{
    // change to enum class
    enum class SwitchesCode
    {
        UP_SWITCH = 0x10,
        BOTTOM_SWITCH = 0x20,
        OK_SWITCH = 0x30,
        CANCEL_SWITCH = 0x40
    };

    enum class SwitchState
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
        static void handleDebounceTimer(int sigNumb, siginfo_t *si, void *uc);
        void changeStateAfterDebounce();

        void initializeCriticalDelay();
        static void handleCriticalDelayTimer(int sigNumb, siginfo_t *si, void *uc);
        void changeOnDelayState();

        void checkErrorInterruptCounter();

    private:
        hardware::GPIOInterface gpio_;
        SwitchesCode code_;
        SwitchState  state_;

        uint8_t errorInterruptCounter_;
        std::function< void(SwitchesCode) > pressedSwitchCallback_;
        std::function< void(SwitchesCode) > errorCallback_;

        const uint32_t CRITICAL_TIME_SEC = 4;
        const uint64_t DEBOUNCE_TIME_NANO_SEC = 1000000;

        utility::Logger& logger_;
    };
}

#endif