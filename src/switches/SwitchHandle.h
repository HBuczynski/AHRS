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

    // Class is responsible for handle one of the button.
    class SwitchHandle final : public utility::TimerInterruptNotification
    {
    public:
        SwitchHandle(hardware::GPIO gpioProperties, SwitchCode code);
        ~SwitchHandle();

        void resetSwitch();
        void initializeCallbacks(std::function< void() > pressedSwitchCallback, std::function< void(SwitchCode, SwitchState) > errorCallback);

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

        SwitchCode code_;
        std::atomic<SwitchState>  state_;

        uint8_t errorInterruptCounter_;
        std::function< void() > pressedSwitchCallback_;
        std::function< void(SwitchCode, SwitchState) > errorCallback_;

        utility::TimerInterrupt debounceTimerID_;
        utility::TimerInterrupt criticalDelayTimerID_;

        const uint32_t CRITICAL_TIME_MS = 4000;
        const uint64_t DEBOUNCE_TIME_MS = 10;

        utility::Logger& logger_;
    };
}

#endif