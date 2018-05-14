#include "SwitcheHandle.h"
#include <thread>
#include <system_error>
#include <iostream>

using namespace std;
using namespace utility;
using namespace hardware;
using namespace peripherals;

SwitcheHandle::SwitcheHandle(hardware::GPIO gpioProperties, SwitchesCode code)
    :  gpio_(gpioProperties),
       code_(code),
       state_(SwitchState::LOW_STATE),
       errorInterruptCounter_(0),
       logger_(Logger::getInstance())
{
    function< void() > raisingCallback = bind(&SwitcheHandle::handleRaisingInterrupt, this);
    function< void() > fallingCallback = bind(&SwitcheHandle::handleFallingInterrupt, this);

    gpio_.activateRaisingInterrupt(raisingCallback);
    gpio_.activateFallingInterrupt(fallingCallback);
}

SwitcheHandle::~SwitcheHandle()
{}

void SwitcheHandle::resetSwitch()
{
    gpio_.pinWrite(0);
    state_ = SwitchState::LOW_STATE;
}

void SwitcheHandle::initializeCallbacks(std::function< void(SwitchesCode) > pressedSwitchCallback, std::function< void(SwitchesCode) > errorCallback)
{
    pressedSwitchCallback_ = pressedSwitchCallback;
    errorCallback_ = errorCallback;
}

void SwitcheHandle::handleRaisingInterrupt()
{
    if(state_ == SwitchState::LOW_STATE)
    {
        state_ = SwitchState::HIGH_BEFORE_DEBOUNCE;

        initializeDebounceTimer();
        initializeCriticalDelay();

        errorInterruptCounter_ = 0;
    }
    else
    {
        checkErrorInterruptCounter();
    }
}

void SwitcheHandle::handleFallingInterrupt()
{
    if(state_ == SwitchState::HIGH_AFTER_DEBONCE)
    {
        pressedSwitchCallback_(code_);
        state_ = SwitchState::LOW_STATE;
    }
    else
    {
        checkErrorInterruptCounter();
    }
}

void SwitcheHandle::checkErrorInterruptCounter()
{
    ++errorInterruptCounter_;

    if(errorInterruptCounter_ >= 200)
    {
        state_ = SwitchState::ERROR_STATE;
        errorCallback_(code_);
    }
}

void SwitcheHandle::initializeDebounceTimer()
{
    timer_t timerID;
    struct sigevent signalEvent;
    struct sigaction signalAction;
    struct itimerspec timerSpecs;

    timerSpecs.it_value.tv_sec = 0;
    timerSpecs.it_value.tv_nsec = DEBOUNCE_TIME_NANO_SEC;
    timerSpecs.it_interval.tv_sec = 0;
    timerSpecs.it_interval.tv_nsec = 0;

    sigemptyset(&signalAction.sa_mask);

    signalAction.sa_flags = SA_SIGINFO;
    signalAction.sa_sigaction = SwitcheHandle::handleDebounceTimer;

    memset(&signalEvent, 0, sizeof(signalEvent));
    signalEvent.sigev_notify = SIGEV_SIGNAL;
    signalEvent.sigev_value.sival_ptr = (void*) this;
    signalEvent.sigev_signo = SIGALRM;

    if (timer_create(CLOCK_REALTIME, &signalEvent, &timerID)!= 0)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitcheHandle :: Could not create debounce timer -- ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (sigaction(SIGALRM, &signalAction, NULL))
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitcheHandle :: Could not install new signal handler debounce timer -- ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (timer_settime(timerID, 0, &timerSpecs, NULL) == -1)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitcheHandle :: Could not start debounce timer -- ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void SwitcheHandle::handleDebounceTimer(int sigNumb, siginfo_t *si, void *uc)
{
    SwitcheHandle * switcheHandleClass = reinterpret_cast<SwitcheHandle *> (si->si_value.sival_ptr);
    switcheHandleClass->changeStateAfterDebounce();
}

void SwitcheHandle::changeStateAfterDebounce()
{
    state_ = SwitchState::HIGH_AFTER_DEBONCE;
}

void SwitcheHandle::initializeCriticalDelay()
{
    timer_t timerID;
    struct sigevent signalEvent;
    struct sigaction signalAction;
    struct itimerspec timerSpecs;

    timerSpecs.it_value.tv_sec = CRITICAL_TIME_SEC;
    timerSpecs.it_value.tv_nsec = 0;
    timerSpecs.it_interval.tv_sec = 0;
    timerSpecs.it_interval.tv_nsec = 0;

    sigemptyset(&signalAction.sa_mask);

    signalAction.sa_flags = SA_SIGINFO;
    signalAction.sa_sigaction = SwitcheHandle::handleCriticalDelayTimer;

    memset(&signalEvent, 0, sizeof(signalEvent));
    signalEvent.sigev_notify = SIGEV_SIGNAL;
    signalEvent.sigev_value.sival_ptr = (void*) this;
    signalEvent.sigev_signo = SIGALRM;

    if (timer_create(CLOCK_REALTIME, &signalEvent, &timerID)!= 0)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitcheHandle :: Could not create delay timer -- ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (sigaction(SIGALRM, &signalAction, NULL))
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitcheHandle :: Could not install new signal handler delay timer -- ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (timer_settime(timerID, 0, &timerSpecs, NULL) == -1)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitcheHandle :: Could not start delay timer -- ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void SwitcheHandle::handleCriticalDelayTimer(int sigNumb, siginfo_t *si, void *uc)
{
    SwitcheHandle * switcheHandleClass = reinterpret_cast<SwitcheHandle *> (si->si_value.sival_ptr);
    switcheHandleClass->changeOnDelayState();
}

void SwitcheHandle::changeOnDelayState()
{
    state_ = SwitchState::ERROR_STATE;
    errorCallback_(code_);
}