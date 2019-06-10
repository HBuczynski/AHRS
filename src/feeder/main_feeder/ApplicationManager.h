#ifndef AHRS_APPLICATIONMANAGER_H
#define AHRS_APPLICATIONMANAGER_H

#include <logger/Logger.h>
#include <thread>
#include <cstdint>
#include <spawn.h>
#include <cstdint>
#include <atomic>

#include <hsm/HSM.h>
#include <time_manager/TimerInterrupt.h>
#include <database_manager/FeederDb.h>
#include <config_reader/FeederParameters.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>

#include <interfaces/communication_process_feeder/FeederNotificationFactory.h>
#include <interfaces/communication_process_feeder/FeederCommandFactory.h>
#include <interfaces/hm/HMCommandFactory.h>

#include <interfaces/hm/HMCommandFactory.h>
#include "ExternalCommunicationVisitor.h"
#include "InternalCommunicationVisitor.h"
#include "HMFeederVisitor.h"

#include "FeederDataContainer.h"

namespace main_process
{
    class ApplicationManager : public hsm::HSM,  public utility::TimerInterruptNotification
    {
    public:
        ApplicationManager(const std::string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState);
        ~ApplicationManager();

        bool initialize();

        FeederDataContainer& getFeederDataContainer();
        void setPlaneName(const std::string& name) noexcept;
        void setHash(uint32_t hash) noexcept;

        void startFeederSystem();
        void stopFeederSystem();

        void sendToExternalCommunicationProcess(std::vector<uint8_t> data);

    private:
        bool initializeMainQueue();
        bool initializeExternalQueue();
        bool initializeInternalQueue();
        bool initializeHMMessageQueue();
        bool initializeCalibrationSharedMemory();

        bool initializeFeederDB();

        bool initializeExternalSharedMemory();
        bool initializeInternalSharedMemory();

        bool createExternalCommunicationProcess();
        bool createInternalCommunicationProcess();

        bool initializeHM();
        void interruptNotification(timer_t timerID) override;

        void restartExternalProcess();
        void restartInternalProcess();

        void runProcessing();
        void handleCommand(const std::vector<uint8_t>& packet);
        void saveGeneralData2DB();

        std::atomic<bool> runDbThread_;
        std::thread dbThread_;

        std::thread processingThread_;
        FeederDataContainer dataContainer_;

        std::shared_ptr<database::FeederDb> feederDb_;

        std::shared_ptr<communication::MessageQueueWrapper> externalComMessageQueue;
        std::shared_ptr<communication::MessageQueueWrapper> internalComMessageQueue;
        std::shared_ptr<communication::MessageQueueWrapper> mainComMessageQueue;
        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;

        std::unique_ptr<communication::SharedMemoryWrapper> externalSharedMemory_;
        std::unique_ptr<communication::SharedMemoryWrapper> internalSharedMemory_;

        config::FeederSharedMemory sharedMemoryParameters_;
        config::FeederMessageQueues messageQueuesParameters_;
        config::FeederExecutableFiles executableFilesNames_;

        ExternalCommunicationVisitor externalVisitor_;
        InternalCommunicationVisitor internalVisitor_;
        std::unique_ptr<main_process::HMFeederVisitor> hmVisitor_;

        communication::FeederNotificationFactory externalNotificationFactory_;
        communication::FeederCommandFactory externalCommandFactory_;
        communication::HMCommandFactory hmCommandFactory_;

        pid_t externalProcess_;
        pid_t internalProcess_;

        std::atomic<bool> runFeederSystem_;
        utility::TimerInterrupt timerInterrupt_;
        utility::Logger &logger_;
    };
}

#endif
