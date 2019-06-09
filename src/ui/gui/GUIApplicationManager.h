#ifndef AHRS_GUIAPPLICATIONMANAGER_H
#define AHRS_GUIAPPLICATIONMANAGER_H

#include "MainWindow.h"
#include "StoryboardsHandler.h"
#include "GUIInterprocessCommandVisitor.h"

#include <interfaces/gui/GUICommandFactory.h>

#include <time_manager/TimerInterrupt.h>
#include <atomic>
#include <memory>
#include <thread>

#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <config_reader/UIParameters.h>

namespace gui
{
    class GUIApplicationManager : public utility::TimerInterruptNotification
    {
    public:
        GUIApplicationManager(std::shared_ptr<MainWindow> mainWindow);
        ~GUIApplicationManager();

        bool initialize();
        void startGUI();
        void stopGUI();

    private:
        bool initializeGUIMessageQueue();
        bool initializeSharedMemory();
        bool initializeHMMessageQueue();
        bool initializeHM();

        void interruptNotification(timer_t timerID) override;

        void interprocessCommunication();
        void handleCommand(const std::vector<uint8_t>& packet);

        std::shared_ptr<MainWindow> mainWindow_;
        std::shared_ptr<GUIInterprocessCommandVisitor> interprocessCommandVisitor_;

        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UISharedMemory uiSharedMemoryParameters_;

        std::unique_ptr<communication::SharedMemoryWrapper> sharedMemory_;

        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;
        std::unique_ptr<communication::MessageQueueWrapper> communicationMessageQueue_;

        std::atomic<bool> runCommunicationThread_;
        std::thread interprocessCommunicationThread_;

        communication::GUICommandFactory commandFactory_;

        utility::TimerInterrupt timerInterrupt_;
        utility::Logger& logger_;
        const uint32_t WELCOME_PAGE_DURATION_MS;
    };
}

#endif
