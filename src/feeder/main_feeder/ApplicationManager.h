#ifndef AHRS_APPLICATIONMANAGER_H
#define AHRS_APPLICATIONMANAGER_H

#include <logger/Logger.h>
#include <thread>
#include <cstdint>
#include <spawn.h>
#include <cstdint>

#include <config_reader/FeederParameters.h>
#include <boost/interprocess/ipc/message_queue.hpp>

#include <interfaces/communication_process_feeder/FeederNotificationFactory.h>
#include <interfaces/communication_process_feeder/FeederCommandFactory.h>

#include "ExternalCommunicationVisitor.h"
#include "InternalCommunicationVisitor.h"

namespace main_process
{
    class ApplicationManager
    {
    public:
        ApplicationManager();
        ~ApplicationManager();

        bool initialize();
        void launchFeederSystem();

    private:
        bool initializeMainQueue();
        bool initializeExternalQueue();
        bool initializeInternalQueue();

        bool initializeExternalSharedMemory();
        bool initializeInternalSharedMemory();

        bool createExternalCommunicationProcess();
        bool createInternalCommunicationProcess();

        void restartExternalProcess();
        void restartInternalProcess();

        void runProcessing();
        void handleCommand(const std::vector<uint8_t>& packet);

        std::thread processingThread_;

        std::shared_ptr<boost::interprocess::message_queue> externalComMessageQueue;
        std::shared_ptr<boost::interprocess::message_queue> internalComMessageQueue;
        std::shared_ptr<boost::interprocess::message_queue> mainComMessageQueue;

        std::unique_ptr<boost::interprocess::named_mutex> externalSharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> externalSharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> externalMappedMemoryRegion_;

        std::unique_ptr<boost::interprocess::named_mutex> internalSharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> internalSharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> internalMappedMemoryRegion_;

        config::FeederSharedMemory sharedMemoryParameters_;
        config::FeederMessageQueues messageQueuesParameters_;
        config::FeederExecutableFiles executableFilesNames_;

        ExternalCommunicationVisitor externalVisitor_;
        InternalCommunicationVisitor internalVisitor_;

        communication::FeederNotificationFactory externalNotificationFactory_;
        communication::FeederCommandFactory externalCommandFactory_;

        pid_t externalProcess_;
        pid_t internalProcess_;

        utility::Logger &logger_;
    };
}

#endif