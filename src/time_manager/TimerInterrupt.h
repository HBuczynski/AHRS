#ifndef AHRS_TIMERINTERRUPT_H
#define AHRS_TIMERINTERRUPT_H

#include <sys/time.h>
#include <string>
#include <cstring>
#include <csignal>
#include <bits/siginfo.h>

#include <logger/Logger.h>

#include "TimerInterruptNotification.h"

namespace utility
{
    class TimerInterrupt
    {
    public:
        TimerInterrupt();
        ~TimerInterrupt();

        void startPeriodic(uint32_t periodInMilliseconds, TimerInterruptNotification* objectToNotify);
        void startSingleInterrupt(uint32_t inMilliseconds, TimerInterruptNotification* objectToNotify);
        void stop();

        timer_t getTimerID() const;

    private:
        struct InterruptObject
        {
            TimerInterruptNotification* objectToNotify;
            timer_t* timerID;
        };

        static void handleInterrupt(int sigNumb, siginfo_t *si, void *uc);

        InterruptObject interruptObject;
        timer_t timerID;
        bool isInitialized_;

        utility::Logger &logger_;
    };
}

#endif
