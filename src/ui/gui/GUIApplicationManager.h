#ifndef AHRS_GUIAPPLICATIONMANAGER_H
#define AHRS_GUIAPPLICATIONMANAGER_H

#include "MainWindow.h"
#include "StoryboardsHandler.h"
#include "GUIInterprocessCommandVisitor.h"

#include <memory>
#include <boost/interprocess/ipc/message_queue.hpp>
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

    private:
        bool initializeGUIMessageQueue();
        bool initializeSharedMemory();

        std::shared_ptr<MainWindow> mainWindow_;
        std::shared_ptr<GUIInterprocessCommandVisitor> interprocessCommandVisitor_;

        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UISharedMemory uiSharedMemoryParameters_;

        std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;

        std::unique_ptr<boost::interprocess::message_queue> communicationMessageQueue_;

        utility::Logger& logger_;
    };
}

#endif
