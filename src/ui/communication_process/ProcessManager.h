#ifndef AHRS_PROCESSMANAGER_H
#define AHRS_PROCESSMANAGER_H

#include <thread>
#include <memory>
#include <atomic>

#include <boost/interprocess/ipc/message_queue.hpp>

#include "CommunicationManagerUI.h"

namespace communication
{
    enum CommunicationProcessMode : uint8_t
    {
        MAIN,
        REDUNDANT
    };

    // Shared memory will be alocated in Data Handler Visitor
    class ProcessManager
    {
    public:
        ProcessManager(std::string managementQueueName, std::string sharedMemoryName, CommunicationProcessMode status);
        ~ProcessManager();

        void run();
        void stopRun();

        CommunicationProcessMode getMode() const;

    private:
        void processReceivingManagementCommand();
        void processSendCommands();

        void performBIT();

        std::unique_ptr<CommunicationManagerUI> communicationManagerUI_;
        CommunicationProcessMode status_;

        std::atomic<bool> runReceivingManagementCommandThread_;
        std::atomic<bool> runSendingCommandThread_;

        std::thread managementThread_;
        std::string managementQueueName_;
        std::string sharedMemoryName_;
    };
}

#endif //AHRS_PROCESSMANAGER_H
