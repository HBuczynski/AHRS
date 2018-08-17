#include <cstdint>
#include <errno.h>
#include <cstdio>
#include <cstdlib>

#include "TimerInterrupt.h"
#include "TimerInterruptNotification.h"

using namespace std;
using namespace utility;

TimerInterrupt::TimerInterrupt()
    : logger_(Logger::getInstance())
{}

TimerInterrupt::~TimerInterrupt()
{
    stop();
}

void TimerInterrupt::startPeriodic(uint32_t periodInMilliseconds, TimerInterruptNotification *objectToNotify)
{
    struct sigevent signalEvent;
    struct sigaction signalAction;
    struct itimerspec timerSpecs;

    uint16_t seconds = periodInMilliseconds / 1000;
    uint32_t  nanoseconds = periodInMilliseconds*1000 - seconds*1000000;

    timerSpecs.it_value.tv_sec = seconds;
    timerSpecs.it_value.tv_nsec = nanoseconds;
    timerSpecs.it_interval.tv_sec = seconds;
    timerSpecs.it_interval.tv_nsec = nanoseconds;

    sigemptyset(&signalAction.sa_mask);

    signalAction.sa_flags = SA_SIGINFO;
    signalAction.sa_sigaction = TimerInterrupt::handleInterrupt;

    memset(&signalEvent, 0, sizeof(signalEvent));
    signalEvent.sigev_notify = SIGEV_SIGNAL;
    signalEvent.sigev_value.sival_ptr = (void*) objectToNotify;
    signalEvent.sigev_signo = SIGALRM;

    if (timer_create(CLOCK_REALTIME, &signalEvent, &timerID)!= 0)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("TimerInterrupt :: Could not create debounce timer");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (sigaction(SIGALRM, &signalAction, NULL))
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("TimerInterrupt :: Could not install new signal.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (timer_settime(timerID, 0, &timerSpecs, NULL) == -1)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("TimerInterrupt :: Could not start timer.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("TimerInterrupt :: Has been initialized.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void TimerInterrupt::startSingle(uint32_t timeInMilliseconds, TimerInterruptNotification* objectToNotify)
{
    struct sigevent signalEvent;
    struct sigaction signalAction;
    struct itimerspec timerSpecs;

    uint16_t seconds = timeInMilliseconds / 1000;
    uint32_t  nanoseconds = timeInMilliseconds*1000 - seconds*1000000;

    timerSpecs.it_value.tv_sec = seconds;
    timerSpecs.it_value.tv_nsec = nanoseconds;
    timerSpecs.it_interval.tv_sec = 0;
    timerSpecs.it_interval.tv_nsec = 0;

    sigemptyset(&signalAction.sa_mask);

    signalAction.sa_flags = SA_SIGINFO;
    signalAction.sa_sigaction = TimerInterrupt::handleInterrupt;

    memset(&signalEvent, 0, sizeof(signalEvent));
    signalEvent.sigev_notify = SIGEV_SIGNAL;
    signalEvent.sigev_value.sival_ptr = (void*) objectToNotify;
    signalEvent.sigev_signo = SIGALRM;

    if (timer_create(CLOCK_REALTIME, &signalEvent, &timerID)!= 0)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("TimerInterrupt :: Could not create debounce timer");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (sigaction(SIGALRM, &signalAction, NULL))
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("TimerInterrupt :: Could not install new signal.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (timer_settime(timerID, 0, &timerSpecs, NULL) == -1)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("TimerInterrupt :: Could not start timer.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void TimerInterrupt::stop()
{
    if(timer_delete(timerID) == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("TimerInterrupt :: Stopped timer correctly.");
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("TimerInterrupt :: Could not stop timer. Errno: ") + strerror(errno);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void TimerInterrupt::handleInterrupt(int sigNumb, siginfo_t *si, void *uc)
{
    TimerInterruptNotification* notification = reinterpret_cast<TimerInterruptNotification*>(si->si_value.sival_ptr);
    notification->interruptNotification();
}
