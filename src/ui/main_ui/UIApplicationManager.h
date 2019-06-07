#ifndef AHRS_PROCESSSCHEDULER_H
#define AHRS_PROCESSSCHEDULER_H

#include <cstdint>
#include <atomic>
#include <memory>
#include <thread>

#include <interfaces/communication_process_ui/UINotificationFactory.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <interfaces/gui/GUIResponseFactory.h>
#include <interfaces/gui/GUICommandFactory.h>
#include <time_manager/TimerInterrupt.h>
#include <config_reader/UIParameters.h>
#include <logger/Logger.h>
#include <hsm/HSM.h>

#include "CommunicationProcessesHandler.h"
#include "GuiProcessHandler.h"

#include "ExternalCommInterprocessVisitor.h"
#include "GUIInterprocessVisitor.h"

#include <database_manager/CockpitDb.h>

namespace main_process
{
    class UIApplicationManager : public hsm::HSM, public utility::TimerInterruptNotification
    {
    public:
        UIApplicationManager(const std::string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState);
        ~UIApplicationManager();

        bool initialize();

        void startUISystem();
        void stopUISystem();

        void sendToGUIProcess(std::vector<uint8_t> data);
        void sendToExternalCommunicationProcess(std::vector<uint8_t> data, config::UICommunicationMode mode);

        uint32_t getDbHash() const noexcept;
        const std::string& getDbName() const noexcept;

        void saveMeasurements2DB();
        void stopMeasurements2DB();

    private:
        bool initializeMainProcessMessageQueue();
        bool initializeHMMessageQueue();
        bool initializeSharedMemory();
        bool initializeDb();
        bool initializeHM();

        void interruptNotification(timer_t timerID) override;

        void handleMessage(const std::vector<uint8_t>& packet);
        void saveGeneral2DB();

        std::shared_ptr<database::CockpitDb> cockpitDb_;

        config::UIWirelessCommunication uiWirelessCommunicationParameters_;
        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UISharedMemory uiSharedMemoryParameters_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> mainMessageQueue_;
        std::unique_ptr<communication::SharedMemoryWrapper> sharedMemory_;

        CommunicationProcessesHandler communicationProcessesHandler_;
        GuiProcessHandler guiProcessHandler_;

        std::unique_ptr<ExternalCommInterprocessVisitor> externalCommunicationVisitor_;
        communication::UINotificationFactory uiNotificationFactory_;
        std::unique_ptr<GUIInterprocessVisitor> guiInterprocessVisitor_;
        
        communication::GUIResponseFactory guiResponseFactory_;
        communication::GUICommandFactory guiCommandFactory_;

        std::atomic<bool> runSavingMeasurements_;
        std::thread dbMeasurementThread_;
        std::atomic<bool> runDbThread_;
        std::thread dbThread_;

        std::atomic<bool> runSystem_;

        utility::TimerInterrupt timerInterrupt_;
        utility::Logger& logger_;
    };
}

#endif
