#include "SwitchHandle.h"
#include <thread>
#include <system_error>
#include <iostream>

using namespace std;
using namespace utility;
using namespace hardware;
using namespace peripherals;

SwitchHandle::SwitchHandle(hardware::GPIO gpioProperties, SwitchCode code)
    :  gpio_(gpioProperties),
       switch_(gpioProperties),
       code_(code),
       state_(SwitchState::HIGH_STATE),
       errorInterruptCounter_(0),
       logger_(Logger::getInstance())
{
    initializeGPIOInterrupts();
}

SwitchHandle::~SwitchHandle()
{
    if(logger_.isDebugEnable())
    {
        const string message = string("SwitchHandle :: Destructor. ");
        logger_.writeLog(LogType::DEBUG_LOG, message);
    }
}

void SwitchHandle::initializeGPIOInterrupts()
{
    bool isSuccess = true;

    isSuccess = isSuccess & switch_.registerHandler(callback, FALLING_EDGE, 0, reinterpret_cast<void*>(this));
    isSuccess = isSuccess & switch_.registerHandler(callback, RISING_EDGE, 0,  reinterpret_cast<void*>(this));

    if(isSuccess)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("SwitchHandle :: Interrupts initialized successful for button: ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitchHandle :: Could not initialize interrupts for buttons: ") + to_string(static_cast<uint8_t>(code_));
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void SwitchHandle::resetSwitch()
{
    gpio_.pinWrite(0);
    state_ = SwitchState::LOW_STATE;
}

void SwitchHandle::initializeCallbacks(std::function< void() > pressedSwitchCallback, std::function< void(SwitchCode, SwitchState) > errorCallback)
{
    pressedSwitchCallback_ = pressedSwitchCallback;
    errorCallback_ = errorCallback;
}

void SwitchHandle::callback(int gpio, int level, uint32_t tick, void *userdata)
{
    SwitchHandle* switchHandle = reinterpret_cast<SwitchHandle*>(userdata);
    if(level == 1)
    {
        switchHandle->handleRaisingInterrupt();
    }
    else
    {
        switchHandle->handleFallingInterrupt();
    }
}

void SwitchHandle::handleRaisingInterrupt()
{
    if(logger_.isDebugEnable())
    {
        const string message = string("SwitchHandle :: HandleRaisingInterrupt, SWITCH: ") + to_string(static_cast<uint8_t>(code_)) + string(" State -- ")
                + to_string(static_cast<uint8_t>(state_.load()));

        logger_.writeLog(LogType::DEBUG_LOG, message);
    }

    if(state_ == SwitchState::LOW_STATE)
    {
        state_ = SwitchState::LOW_DEBOUNCE_SECTION;
        debounceTimerID_.startSingleInterrupt(DEBOUNCE_TIME_MS, this);
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

void SwitchHandle::handleFallingInterrupt()
{
    if(logger_.isDebugEnable())
    {
        const string message = string("SwitchHandle :: HandleFallingInterrupt, SWITCH: ") + to_string(static_cast<uint8_t>(code_)) + string(" State -- ")
                               + to_string(static_cast<uint8_t>(state_.load()));

        logger_.writeLog(LogType::DEBUG_LOG, message);
    }

    if(state_ == SwitchState::HIGH_STATE)
    {
        state_ = SwitchState::HIGH_DEBOUNCE_SECTION;

        debounceTimerID_.startSingleInterrupt(DEBOUNCE_TIME_MS, this);
        criticalDelayTimerID_.startSingleInterrupt(CRITICAL_TIME_MS, this);
    }
    else
    {
        checkErrorInterruptCounter();
    }
}

void SwitchHandle::checkErrorInterruptCounter()
{
    ++errorInterruptCounter_;

    if(errorInterruptCounter_ >= 20)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("SwitchHandle :: Exceeded debounce counter, SWITCH: ") + to_string(static_cast<uint8_t>(code_)) + string(" State -- ")
                                   + to_string(static_cast<uint8_t>(state_.load()));

            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        state_ = SwitchState::ERROR_DEBOUNCE;
        errorCallback_(code_, state_);
    }

    state_ = SwitchState::HIGH_STATE;
}

void SwitchHandle::interruptNotification(timer_t timerID)
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

void SwitchHandle::changeStateAfterDebounce()
{
    if(state_ == SwitchState::HIGH_DEBOUNCE_SECTION)
    {
        state_ = SwitchState::LOW_STATE;
        errorInterruptCounter_ = 0;

    }
    else if(state_ == SwitchState::LOW_DEBOUNCE_SECTION)
    {
        criticalDelayTimerID_.stop();

        state_ = SwitchState::HIGH_STATE;
        errorInterruptCounter_ = 0;

        pressedSwitchCallback_();
    }
}

void SwitchHandle::changeOnDelayState()
{
    if(logger_.isErrorEnable())
    {
        const string message = string("SwitchHandle :: Exceeded critical pressing time, SWITCH: ") + to_string(static_cast<uint8_t>(code_)) + string(" State -- ")
                               + to_string(static_cast<uint8_t>(state_.load()));

        logger_.writeLog(LogType::ERROR_LOG, message);
    }

    state_ = SwitchState::ERROR_CRITICAL_TIME;
    errorCallback_(code_, state_);
}