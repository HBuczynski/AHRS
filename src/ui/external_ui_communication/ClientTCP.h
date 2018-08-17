#ifndef AHRS_BLACK_BOX_WAIC_CLIENT_H
#define AHRS_BLACK_BOX_WAIC_CLIENT_H

#include <atomic>
#include <queue>
#include <thread>
#include <mutex>

#include <logger/Logger.h>
#include <packet/SendStreamTCP.h>
#include <interfaces/wireless_commands/Command.h>
#include <interfaces/wireless_responses/ResponseFactory.h>
#include "ResponseHandlerVisitor.h"

namespace communication
{
    class ClientTCP
    {
    public:
        ClientTCP(uint16_t portIn, std::string addressIn);
        ~ClientTCP();

        bool connectToServer();

        void stopCommandSending();
        void startCommandSending();

        void sendCommand(std::unique_ptr<Command> command);
//        bool isResponseQueueEmpty();
//        std::unique_ptr<Response> getResponse();


    private:
        bool isCommandQueueEmpty();
        std::unique_ptr<Command> getFromCommandQueue();

        //void insertToResponseQueue(std::unique_ptr<Response> command);

        void executeCommands();
        void catchExceptions(std::string exception, bool isEndConnectionSent, uint8_t commandSendingCounter);

        uint16_t port_;
        std::string address_;

        std::unique_ptr<SendStreamTCP> socket_;

        std::atomic<bool> executeCommandsFlag_;
        std::thread executeCommandThread_;

        std::mutex commandQueueMutex_;
        std::queue<std::unique_ptr<Command>> commandQueue_;

//        std::mutex responseQueueMutex_;
//        std::queue<std::unique_ptr<Response> > responseQueue_;

        ResponseHandlerVisitor responseHandler_;
        ResponseFactory responseFactory_;

        const uint8_t COMMAND_SENDING_REPETITION = 5;

        utility::Logger& logger_;
    };

}
#endif
