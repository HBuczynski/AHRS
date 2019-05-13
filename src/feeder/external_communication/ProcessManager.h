#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include "ServerTCP.h"
#include "ClientUDP.h"
#include "InterprocessExtCommunicationVisitor.h"

#include <interfaces/communication_process_feeder/FeederNotificationFactory.h>
#include <interfaces/communication_process_feeder/FeederCommandFactory.h>

#include <memory>
#include <utility>
#include <thread>
#include <mutex>
#include <atomic>

#include <logger/Logger.h>
#include <config_reader/FeederParameters.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>


namespace communication
{
    class ProcessManager
    {
    public:
        ProcessManager(const std::string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState);

        bool initialize();
        void start();
        void stop();

    private:
        bool initializeWirelesslCommunication();
        bool initializeMessageQueueCommunication();

        void sendMessageToMainProcess(std::vector<uint8_t> &data);

        config::FeederExternalWireless feederExternalWirelessParameters_;
        config::FeederMessageQueues messageQueuesParameters_;

        config::FeederType feederType_;

        std::shared_ptr<ServerTCP> server_;
        std::shared_ptr<ClientUDPManager> clientUDPManager_;

        InterprocessExtCommunicationVisitor interprocessVisitor_;
        communication::FeederNotificationFactory notificationFactory_;
        communication::FeederCommandFactory commandFactory_;
        

        std::shared_ptr<communication::MessageQueueWrapper> receivingMessageQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> sendingMessageQueue_;

        std::atomic<bool> runConfigurationProcess_;
        utility::Logger &logger_;
    };
}
#endif
