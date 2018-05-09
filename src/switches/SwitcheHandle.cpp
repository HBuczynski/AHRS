#include "SwitcheHandle.h"
#include <thread>
#include <system_error>
#include <signal.h>
#include <sys/time.h>

using namespace std;
using namespace hardware;
using namespace peripherals;

SwitcheHandle::SwitcheHandle(hardware::GPIO gpioProperties, SwitchesCode code)
    :  gpio_(gpioProperties),
       code_(code),
       state_(SwitchState::LOW_STATE),
       errorInterruptCounter_(0)
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
    struct timeval my_value={0,DEBOUNCE_TIME_MICRO_SEC};
    struct timeval my_interval={0,0};
    struct itimerval my_timer={my_interval,my_value};

    setitimer(ITIMER_REAL, &my_timer, 0);
    //signal(SIGALRM, (sighandler_t) changeStateAfterDebounce);
}

void SwitcheHandle::changeStateAfterDebounce(int)
{
    state_ = SwitchState::HIGH_AFTER_DEBONCE;
}

void SwitcheHandle::initializeCriticalDelay()
{
    struct timeval my_value={CRITICAL_TIME_SEC,0};
    struct timeval my_interval={0,0};
    struct itimerval my_timer={my_interval,my_value};

    setitimer(ITIMER_REAL, &my_timer, 0);
    //signal(SIGALRM, (sighandler_t) changeOnDelayState);
}

void SwitcheHandle::changeOnDelayState(int)
{
    state_ = SwitchState::ERROR_STATE;
    errorCallback_(code_);
}