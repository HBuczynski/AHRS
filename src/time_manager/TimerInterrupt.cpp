#include <cstdint>
#include "TimerInterrupt.h"
#include "TimerInterruptNotification.h"

using namespace std;
using namespace utility;

TimerInterrupt::TimerInterrupt()
{}

TimerInterrupt::~TimerInterrupt()
{
    stop();
}

void TimerInterrupt::start(uint32_t periodInMilliseconds, TimerInterruptNotification *objectToNotify)
{

}

void TimerInterrupt::stop()
{

}
