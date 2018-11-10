#ifndef AHRS_PROCESSSCHEDULER_H
#define AHRS_PROCESSSCHEDULER_H

#include <cstdint>
#include <atomic>
#include <memory>

#include <logger/Logger.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <config_reader/UIParameters.h>
#include <interfaces/gui/GUIResponseFactory.h>
#include <interfaces/communication_process_ui/UINotificationFactory.h>
#include <interfaces/gui/GUICommandFactory.h>

#include "CommunicationProcessesHandler.h"
#include "GuiProcessHandler.h"

#include "ExternalCommInterprocessVisitor.h"
#include "GUIInterprocessVisitor.h"

#include "machine_state/UIAbstractState.h"

namespace main_process
{
    class UIApplicationManager
    {
    public:
        UIApplicationManager();
        ~UIApplicationManager();

        bool initialize();

        void startUISystem();
        void stopUISystem();

        /***** Machine State methods *****/
        void setWelcomePage();
        void communicationInProgress();
        void setInformationPage(uint8_t master, uint8_t redundant, uint8_t bitMaster, uint8_t bitRedundant);
        void sendToExternalCommunicationProcess(std::vector<uint8_t> data, config::UICommunicationMode mode);

        void setNewState(UIAbstractState *newState);
        /***** END Machine State *****/

    private:
        bool initializeMainProcessMessageQueue();
        bool initializeSharedMemory();

        void handleMessage(const std::vector<uint8_t>& packet);

        config::UIWirelessCommunication uiWirelessCommunicationParameters_;
        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UISharedMemory uiSharedMemoryParameters_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        std::shared_ptr<communication::MessageQueueWrapper> mainMessageQueue_;
        std::unique_ptr<communication::SharedMemoryWrapper> sharedMemory_;

        CommunicationProcessesHandler communicationProcessesHandler_;
        GuiProcessHandler guiProcessHandler_;
        std::unique_ptr<UIAbstractState> currentState_;

        std::unique_ptr<ExternalCommInterprocessVisitor> externalCommunicationVisitor_;
        communication::UINotificationFactory uiNotificationFactory_;
        std::unique_ptr<GUIInterprocessVisitor> guiInterprocessVisitor_;
        
        communication::GUIResponseFactory guiResponseFactory_;
        communication::GUICommandFactory guiCommandFactory_;

        std::atomic<bool> runSystem_;
        utility::Logger& logger_;
    };
}

#endif
