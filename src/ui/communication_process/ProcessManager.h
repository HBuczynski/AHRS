#ifndef AHRS_PROCESSMANAGER_H
#define AHRS_PROCESSMANAGER_H

#include <thread>
#include <memory>
#include <atomic>

#include <boost/interprocess/ipc/message_queue.hpp>

#include <logger/Logger.h>
#include <communication_manager_ui/CommunicationManagerUI.h>

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

    private:
        void initialization();
        void processReceivingManagementCommand();

        void changeMode(CommunicationProcessMode mode);

        void performBIT();
        void stopRun();

        std::unique_ptr<CommunicationManagerUI> communicationManagerUI_;
        CommunicationProcessMode status_;

        std::atomic<bool> runReceivingManagementCommandThread_;
        std::atomic<bool> runSendingCommandThread_;
        std::thread managementThread_;

        std::unique_ptr<boost::interprocess::message_queue> messageQueue_;
        std::string managementQueueName_;
        std::string sharedMemoryName_;

        utility::Logger& logger_;
    };
}

#endif //AHRS_PROCESSMANAGER_H
