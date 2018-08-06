#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include "ServerTCP.h"
#include "ClientUDP.h"

#include <memory>
#include <utility>
#include <thread>
#include <mutex>

#include <logger/Logger.h>
#include <config_reader/FeederParameters.h>
#include <boost/interprocess/ipc/message_queue.hpp>


namespace communication
{
    class ProcessManager
    {
    public:
        ProcessManager();
        ~ProcessManager();

        void runProcessConfiguration();

    private:
        void initializeExternalCommmunication();
        void initializeMessageQueueCommunication();
        void initializeSharedMemoryCommunication();

        config::FeederExternalWireless feederExternalWirelessParameters_;
        config::FeederSharedMemory sharedMemoryParameters_;
        config::FeederMessageQueues messageQueuesParameters_;

        config::FeederType feederType_;

        std::shared_ptr<ServerTCP> server_;
        std::shared_ptr<ClientUDPManager> clientUDPManager_;
        

        std::shared_ptr<boost::interprocess::message_queue> messageQueue;

        std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;

        utility::Logger &logger_;
    };
}
#endif