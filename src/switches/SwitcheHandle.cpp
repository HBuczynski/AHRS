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
    initializeGPIOInterrupts();
}

SwitcheHandle::~SwitcheHandle()
{}

void SwitcheHandle::initializeGPIOInterrupts()
{
    bool isSuccess = true;

    isSuccess = isSuccess & switch_.registerHandler(callback, FALLING_EDGE, 0, reinterpret_cast<void*>(this));
    isSuccess = isSuccess & switch_.registerHandler(callback, RISING_EDGE, 0,  reinterpret_cast<void*>(this));

    if(isSuccess)
    {
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

void SwitcheHandle::initializeCallbacks(std::function< void() > pressedSwitchCallback, std::function< void(SwitchState) > errorCallback)
{
    pressedSwitchCallback_ = pressedSwitchCallback;
    errorCallback_ = errorCallback;
}

void SwitcheHandle::callback(int gpio, int level, uint32_t tick, void *userdata)
{
    SwitcheHandle* switchHandle = reinterpret_cast<SwitcheHandle*>(userdata);
    if(level == 1)
    {
        switchHandle->handleRaisingInterrupt();
    }
    else
    {
        switchHandle->handleFallingInterrupt();
    }
}

void SwitcheHandle::handleRaisingInterrupt()
{
    if(state_ == SwitchState::LOW_STATE)
    {
        state_ = SwitchState::LOW_DEBOUNCE_SECTION;
        debounceTimerID_.startSingleInterrupt(DEBOUNCE_TIME_MSSEC, this);
    }
    else if(state_ == SwitchState::ERROR_CRITICAL_TIME)
    {
        state_ = SwitchState::HIGH_STATE;
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
        state_ = SwitchState::HIGH_DEBOUNCE_SECTION;

        debounceTimerID_.startSingleInterrupt(DEBOUNCE_TIME_MSSEC, this);
        criticalDelayTimerID_.startSingleInterrupt(CRITICAL_TIME_MSSEC, this);
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
        errorCallback_(state_);
    }

    state_ = SwitchState::HIGH_STATE;
}

void SwitcheHandle::interruptNotification(timer_t timerID)
{
    if(timerID == debounceTimerID_.getTimerID())
    {
        changeStateAfterDebounce();
    }
    else if (timerID == criticalDelayTimerID_.getTimerID())
    {
        changeOnDelayState();
    }
}

void SwitcheHandle::changeStateAfterDebounce()
{
    if(state_ == SwitchState::HIGH_DEBOUNCE_SECTION)
    {
        state_ = SwitchState::LOW_STATE;
        errorInterruptCounter_ = 0;

    }
    else if(state_ == SwitchState::LOW_DEBOUNCE_SECTION)
    {
        criticalDelayTimerID_.stop();
        pressedSwitchCallback_();

        state_ = SwitchState::HIGH_STATE;
        errorInterruptCounter_ = 0;
    }
}

void SwitcheHandle::changeOnDelayState()
{
    state_ = SwitchState::ERROR_CRITICAL_TIME;
    errorCallback_(state_);
}