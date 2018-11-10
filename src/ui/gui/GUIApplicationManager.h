#ifndef AHRS_GUIAPPLICATIONMANAGER_H
#define AHRS_GUIAPPLICATIONMANAGER_H

#include "MainWindow.h"
#include "StoryboardsHandler.h"
#include "GUIInterprocessCommandVisitor.h"

#include <interfaces/gui/GUICommandFactory.h>

#include <atomic>
#include <memory>
#include <thread>

#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <config_reader/UIParameters.h>

namespace gui
{
    class GUIApplicationManager
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

        void interprocessCommunication();
        void handleCommand(const std::vector<uint8_t>& packet);

        std::shared_ptr<MainWindow> mainWindow_;
        std::shared_ptr<GUIInterprocessCommandVisitor> interprocessCommandVisitor_;

        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UISharedMemory uiSharedMemoryParameters_;

        std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;

        std::unique_ptr<communication::MessageQueueWrapper> communicationMessageQueue_;

        std::atomic<bool> runCommunicationThread_;
        std::thread interprocessCommunicationThread_;

        communication::GUICommandFactory commandFactory_;

        utility::Logger& logger_;
        const uint32_t WELCOME_PAGE_DURATION_MS;
    };
}

#endif
