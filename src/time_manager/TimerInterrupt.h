#ifndef AHRS_TIMERINTERRUPT_H
#define AHRS_TIMERINTERRUPT_H

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