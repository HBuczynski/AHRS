#ifndef INTERMANAGER_H
#define INTERMANAGER_H

#include <time_manager/TimerInterrupt.h>
#include <config_reader/FeederParameters.h>
#include <logger/Logger.h>

#include "InterClientTCP.h"

namespace communication
{
    class InterManager final : public utility::TimerInterruptNotification
    {
    public:
        InterManager();
        ~InterManager();

        void launchTimer();
        void sendCommands(std::unique_ptr<communication::Command> commandIn);

    private:
        bool connectToFeeder();

        void interruptNotification(timer_t timerID);

        config::FeederInternalWireless internalCommunicationParameters_;
        utility::TimerInterrupt connectionEstablishingInterrupt_;

        std::unique_ptr<InterClientTCP> client_;

        std::atomic<bool> connectionEstablished_;
        utility::Logger& logger_;
    };
}
#endif // INTERMANAGER_H
