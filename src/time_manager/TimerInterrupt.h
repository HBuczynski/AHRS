#ifndef AHRS_TIMERINTERRUPT_H
#define AHRS_TIMERINTERRUPT_H

#include "TimerInterruptNotification.h"

namespace utility
{
    class TimerInterrupt
    {
    public:
        TimerInterrupt();
        ~TimerInterrupt();

        void start(uint32_t periodInMilliseconds, TimerInterruptNotification* objectToNotify);
        void stop();

    private:
    };
}

#endif