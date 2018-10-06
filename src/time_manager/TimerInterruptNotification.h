#ifndef AHRS_TIMERINTERRUPTNOTIFICATION_H
#define AHRS_TIMERINTERRUPTNOTIFICATION_H

#include <sys/time.h>

namespace utility
{
    class TimerInterruptNotification
    {
    public:
        TimerInterruptNotification() {};
        virtual ~TimerInterruptNotification() {};

        virtual void interruptNotification(timer_t timerID) = 0;
    };
}

#endif
