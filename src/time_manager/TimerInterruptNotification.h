#ifndef AHRS_TIMERINTERRUPTNOTIFICATION_H
#define AHRS_TIMERINTERRUPTNOTIFICATION_H

namespace utility
{
    class TimerInterruptNotification
    {
    public:
        TimerInterruptNotification() {};
        virtual ~TimerInterruptNotification() {};

        virtual void interruptNotification() = 0;
    };
}

#endif