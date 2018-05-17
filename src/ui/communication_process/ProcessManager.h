#ifndef AHRS_PROCESSMANAGER_H
#define AHRS_PROCESSMANAGER_H

#include <boost/interprocess/ipc/message_queue.hpp>

#include <thread>
#include <memory>
#include <atomic>

#include <communication_manager_ui/CommunicationManagerUI.h>
#include <interfaces/wireless_commands/CommandFactory.h>
#include <interfaces/interprocess_ui_commands/UICommandFactory.h>
#include <interfaces/interprocess_ui_commands/UICommandVisitor.h>

#include <logger/Logger.h>

namespace communication
{
    class ProcessManager : public UICommandVisitor
    {
    public:
        ProcessManager(std::string managementQueueName, std::string sharedMemoryName, CommunicationProcessMode status);
        ~ProcessManager();

        void run();
        void stopRun();

        void visit(UIChangeModeCommand& command) override;

    private:
        void initialize();
        void openQueue();
        void initializeWirelessCommunication();

        void processReceivingManagementCommand();
        void handleMessage(const std::vector<uint8_t > &data);

        void changeMode(CommunicationProcessMode mode);

        void performBIT();

        communication::CommandFactory wirelessCommandFactory_;
        communication::UICommandFactory uiCommandFactory_;

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
