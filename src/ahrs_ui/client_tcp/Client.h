#ifndef AHRS_BLACK_BOX_WAIC_CLIENT_H
#define AHRS_BLACK_BOX_WAIC_CLIENT_H

#include "ResponseNotification.h"

#include <packet/SendStreamTCP.h>
#include <protocol/Command.h>

#include <cstdint>
#include <atomic>
#include <string>
#include <memory>
#include <utility>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

namespace communication
{
    typedef std::pair<std::unique_ptr<Command>, ResponseNotification*> CommandInQueue;
    class Client
    {
    public:
        Client(uint16_t portIn, std::string addressIn);
        ~Client();

        void stopCommandSending();
        void startCommandSending();
        void sendCommand(std::unique_ptr<Command> command, ResponseNotification *notification);


    private:
        bool isQueueEmpty();
        CommandInQueue getFromQueue();
        void insertToQueue(CommandInQueue command);

        void executeCommands();

        uint16_t port_;
        std::string address_;

        std::unique_ptr<SendStreamTCP> socket_;

        std::atomic<bool> executeCommandsFlag_;
        std::mutex commandQueueMutex_;
        std::thread executeCommandThread_;

        std::condition_variable conditionVariable_;
        std::mutex conditionalVariableMutex_;

        std::queue<CommandInQueue> commandQueue_;

        const uint8_t COMMAND_SENDING_REPETITION = 5;
    };

}
#endif
