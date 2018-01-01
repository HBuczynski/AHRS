#ifndef AHRS_BLACK_BOX_WAIC_CLIENT_H
#define AHRS_BLACK_BOX_WAIC_CLIENT_H

#include <ahrs_ui/client_tcp/ResponseNotification.h>
#include <ahrs_ui/client_tcp/ResponseHandlerVisitor.h>
#include <logger/Logger.h>
#include <packet/SendStreamTCP.h>
#include <protocol/Command.h>
#include <protocol/ResponseFactory.h>

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
    class ClientTCP
    {
    public:
        ClientTCP(uint16_t portIn, std::string addressIn);
        ~ClientTCP();

        void connectToServer();

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

        ResponseHandlerVisitor responseHandler_;
        ResponseFactory responseFactory_;

        const uint8_t COMMAND_SENDING_REPETITION = 5;

        utility::Logger& logger_;
    };

}
#endif
