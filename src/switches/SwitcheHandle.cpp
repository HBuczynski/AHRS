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
       switch_(gpioProperties),
       code_(code),
       state_(SwitchState::HIGH_STATE),
       errorInterruptCounter_(0),
       logger_(Logger::getInstance())
{
    initializeInterrupts();
}

SwitcheHandle::~SwitcheHandle()
{}

void SwitcheHandle::initializeInterrupts()
{
    bool isSuccess = true;

    isSuccess = isSuccess & switch_.registerHandler(callback, FALLING_EDGE, 0, reinterpret_cast<void*>(this));
    isSuccess = isSuccess & switch_.registerHandler(callback, RISING_EDGE, 0,  reinterpret_cast<void*>(this));

    if(isSuccess)
    {
        cout << "SwitcheHandle :: Interrupts initialized successful for button: " + to_string(static_cast<uint8_t>(code_)) << endl;

        if(logger_.isInformationEnable())
        {
            const string message = string("SwitcheHandle :: Interrupts initialized successful for button: ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitcheHandle :: Could not initialize interrupts for buttons: ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void SwitcheHandle::resetSwitch()
{
    gpio_.pinWrite(0);
    state_ = SwitchState::LOW_STATE;
}

void SwitcheHandle::initializeCallbacks(std::function< void() > pressedSwitchCallback, std::function< void(SwitchesCode) > errorCallback)
{
    pressedSwitchCallback_ = pressedSwitchCallback;
    errorCallback_ = errorCallback;
}

void SwitcheHandle::callback(int gpio, int level, uint32_t tick, void *userdata)
{
    SwitcheHandle* switchHandle = reinterpret_cast<SwitcheHandle*>(userdata);
    if(level == 1)
    {
        cout << "In callback: Raising Interrupt" << endl;
        switchHandle->handleRaisingInterrupt();
    }
    else
    {
        cout << "In callback: Falling Interrupt" << endl;
        switchHandle->handleFallingInterrupt();
    }
}

void SwitcheHandle::handleRaisingInterrupt()
{
    if(state_ == SwitchState::LOW_STATE)
    {
        cout << "In handleRaisingInterrupt: LOW_DEBOUNCE_SECTION" << endl;
        state_ = SwitchState::LOW_DEBOUNCE_SECTION;
        initializeDebounceTimer();
    }
    else
    {
        checkErrorInterruptCounter();
    }
}

void SwitcheHandle::handleFallingInterrupt()
{
    if(state_ == SwitchState::HIGH_STATE)
    {
        cout << "IN handleFallingInterrupt: HIGH_DEBOUNCE_SECTION" << endl;
        state_ = SwitchState::HIGH_DEBOUNCE_SECTION;

        initializeDebounceTimer();
        initializeCriticalDelay();

    }
    else
    {
        checkErrorInterruptCounter();
    }
}

void SwitcheHandle::checkErrorInterruptCounter()
{
    ++errorInterruptCounter_;

    if(errorInterruptCounter_ >= 20)
    {
        state_ = SwitchState::ERROR_DEBOUNCE;
        errorCallback_(code_);
    }
}

void SwitcheHandle::initializeDebounceTimer()
{
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

    if (timer_create(CLOCK_REALTIME, &signalEvent, &debounceTimerID_)!= 0)
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

    if (timer_settime(debounceTimerID_, 0, &timerSpecs, NULL) == -1)
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
    cout << "AFTER DEB:   ";
    if(state_ == SwitchState::HIGH_DEBOUNCE_SECTION)
    {
        cout << "IRQ: LOW_STATE" << endl;
        state_ = SwitchState::LOW_STATE;
        errorInterruptCounter_ = 0;

    }
    else if(state_ == SwitchState::LOW_DEBOUNCE_SECTION)
    {
        cout << "IRQ: HIGHT_STATE" << endl;
        pressedSwitchCallback_();
        state_ = SwitchState::HIGH_STATE;
        errorInterruptCounter_ = 0;
    }
}

void SwitcheHandle::initializeCriticalDelay()
{
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

    if (timer_create(CLOCK_REALTIME, &signalEvent, &criticalDelayTimerID_)!= 0)
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

    if (timer_settime(criticalDelayTimerID_, 0, &timerSpecs, NULL) == -1)
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
    state_ = SwitchState::ERROR_CRITICAL_TIME;
    errorCallback_(code_);

    state_ = SwitchState::HIGH_STATE;
}