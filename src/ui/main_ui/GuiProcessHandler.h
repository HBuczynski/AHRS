#ifndef AHRS_GUIPROCESSHANDLER_H
#define AHRS_GUIPROCESSHANDLER_H

#include <utility>
#include <string>
#include <cstdint>
#include <spawn.h>
#include <cstdint>
#include <atomic>

#include <logger/Logger.h>
#include <config_reader/UIParameters.h>
#include <boost/interprocess/ipc/message_queue.hpp>

namespace main_process
{
    class GuiProcessHandler
    {
    public:
        GuiProcessHandler();
        ~GuiProcessHandler();

        bool initialize();
        void resetProcess();

    private:
        bool initializeMessageQueue();
        bool launchProcess();

        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UIExecutableFiles uiExecutableFiles_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        std::shared_ptr<boost::interprocess::message_queue> communicationMessageQueue;

        pid_t pid;
        utility::Logger& logger_;
    };
}

#endif
