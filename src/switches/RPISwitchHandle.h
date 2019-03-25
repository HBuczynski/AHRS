#ifndef AHRS_SWITCHESHANDLE_H
#define AHRS_SWITCHESHANDLE_H

#include <time_manager/TimerInterrupt.h>
#include <logger/Logger.h>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <string>
#include <cstring>
#include <csignal>
#include <atomic>

#include <bits/siginfo.h>

#include "SwitchHandle.h"

namespace  peripherals
{
    // Class is responsible for handle one of the button.
    class RPISwitchHandle final : public utility::TimerInterruptNotification, public SwitchHandle
    {
    public:
        RPISwitchHandle(hardware::GPIO gpioProperties, SwitchCode code);
        ~RPISwitchHandle();

        virtual void resetSwitch() override ;
        virtual void initializeCallbacks(std::function< void() > pressedSwitchCallback, std::function< void(SwitchCode, SwitchState) > errorCallback) override;

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