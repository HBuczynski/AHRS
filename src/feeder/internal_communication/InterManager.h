#ifndef INTERMANAGER_H
#define INTERMANAGER_H

#include <message_queue_wrapper/MessageQueueWrapper.h>

#include <time_manager/TimerInterrupt.h>
#include <config_reader/FeederParameters.h>
#include <logger/Logger.h>

#include "InterClientTCP.h"
#include "EthServerUDP.h"
#include "InterCommunicationVisitor.h"

namespace communication
{
    class InterManager final : public utility::TimerInterruptNotification
    {
    public:
        InterManager();
        ~InterManager();

        bool initialize();

        void startCommunication();
        void stopCommunication();

        void sendCommands(std::unique_ptr<communication::EthFeederCommand> commandIn);

    private:
        bool initializeMainMessageQueue();
        bool initializeHMMessageQueue();
        bool initializeCommunicationProcessMessageQueue();

        void initInformation();
        bool initializeHM();

        void launchTimer();
        bool connectToFeeder();

        void interruptNotification(timer_t timerID);
        void sendHeartbeat();
        void initConnection();

        config::FeederMessageQueues feederQueuesParameters_;
        config::FeederInternalWireless internalCommunicationParameters_;
        utility::TimerInterrupt connectionEstablishingInterrupt_;

        std::unique_ptr<InterClientTCP> client_;
        std::unique_ptr<EthServerUDP> server_;
        InterCommunicationVisitor communicationVisitor_;

        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;
        std::unique_ptr<communication::MessageQueueWrapper> mainMessageQueue_;
        std::unique_ptr<communication::MessageQueueWrapper> receivingMessageQueue_;

        std::atomic<bool> runCommunicationProcess_;
        std::atomic<bool> connectionEstablished_;

        utility::TimerInterrupt hmTimerInterrupt_;
        utility::Logger& logger_;
    };
}
#endif // INTERMANAGER_H
