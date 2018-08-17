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
        void startSingle(uint32_t timeInMilliseconds, TimerInterruptNotification* objectToNotify);
        void stop();

    private:
        static void handleInterrupt(int sigNumb, siginfo_t *si, void *uc);

        timer_t timerID;

        utility::Logger& logger_;
    };
}

#endif