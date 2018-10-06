#ifndef AHRS_SWITCHESHANDLE_H
#define AHRS_SWITCHESHANDLE_H

#include <logger/Logger.h>
#include <hal/include/GPIOInterface.h>
#include <time_manager/TimerInterrupt.h>
#include <hal/include/Switch.h>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <string>
#include <cstring>
#include <csignal>
#include <atomic>

#include <bits/siginfo.h>

namespace  peripherals
{
    enum class SwitchesCode : uint8_t
    {
        FIRST_SWITCH = 0x01,
        SECOND_SWITCH = 0x02,
        THIRD_SWITCH = 0x03,
        FOURTH_SWITCH = 0x04
    };

    enum class SwitchState : uint8_t
    {
        LOW_DEBOUNCE_SECTION,
        LOW_STATE,
        HIGH_DEBOUNCE_SECTION,
        HIGH_STATE,
        ERROR_CRITICAL_TIME,
        ERROR_DEBOUNCE,
    };

    // Class is responsible for handle one of the button.
    class SwitcheHandle final : public utility::TimerInterruptNotification
    {
    public:
        SwitcheHandle(hardware::GPIO gpioProperties, SwitchesCode code);
        ~SwitcheHandle();

        void resetSwitch();
        void initializeCallbacks(std::function< void() > pressedSwitchCallback, std::function< void(SwitchState) > errorCallback);

    private:
        void initializeGPIOInterrupts();
        static void callback(int gpio, int level, uint32_t tick, void *userdata);

        void handleFallingInterrupt();
        void handleRaisingInterrupt();

        void interruptNotification(timer_t timerID);
        void changeStateAfterDebounce();
        void changeOnDelayState();

        void checkErrorInterruptCounter();

    private:
        hardware::GPIOInterface gpio_;
        hardware::Switch switch_;

        SwitchesCode code_;
        std::atomic<SwitchState>  state_;

        uint8_t errorInterruptCounter_;
        std::function< void() > pressedSwitchCallback_;
        std::function< void(SwitchState) > errorCallback_;

        utility::TimerInterrupt debounceTimerID_;
        utility::TimerInterrupt criticalDelayTimerID_;

        const uint32_t CRITICAL_TIME_MSSEC = 4000;
        const uint64_t DEBOUNCE_TIME_MSSEC = 10;

        utility::Logger& logger_;
    };
}

#endif