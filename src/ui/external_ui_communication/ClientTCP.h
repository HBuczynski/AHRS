#ifndef AHRS_BLACK_BOX_WAIC_CLIENT_H
#define AHRS_BLACK_BOX_WAIC_CLIENT_H

#include "ResponseHandlerVisitor.h"
#include "../../logger/Logger.h"
#include "../../packet/SendStreamTCP.h"
#include "../../interfaces/wireless_commands/Command.h"
#include "../../interfaces/wireless_responses/ResponseFactory.h"

#include "../../../../../../../../usr/include/c++/5/cstdint"
#include "../../../../../../../../usr/include/c++/5/atomic"
#include "../../../../../../../../usr/include/c++/5/string"
#include "../../../../../../../../usr/include/c++/5/memory"
#include "../../../../../../../../usr/include/c++/5/utility"
#include "../../../../../../../../usr/include/c++/5/mutex"
#include "../../../../../../../../usr/include/c++/5/thread"
#include "../../../../../../../../usr/include/c++/5/queue"
#include "../../../../../../../../usr/include/c++/5/condition_variable"

namespace communication
{
    class ClientTCP
    {
    public:
        ClientTCP(uint16_t portIn, std::string addressIn);
        ~ClientTCP();

        void connectToServer();

        void stopCommandSending();
        void startCommandSending();

        void sendCommand(std::unique_ptr<Command> command);
        bool isResponseQueueEmpty();
        std::unique_ptr<Response> getResponse();


    private:
        bool isCommandQueueEmpty();
        std::unique_ptr<Command> getFromCommandQueue();

        void insertToResponseQueue(std::unique_ptr<Response> command);

        void executeCommands();
        void catchExceptions(std::string exception, bool isEndConnectionSent, uint8_t commandSendingCounter);

        uint16_t port_;
        std::string address_;

        std::unique_ptr<SendStreamTCP> socket_;

        std::atomic<bool> executeCommandsFlag_;
        std::thread executeCommandThread_;

        std::mutex commandQueueMutex_;
        std::queue<std::unique_ptr<Command>> commandQueue_;

        std::mutex responseQueueMutex_;
        std::queue<std::unique_ptr<Response> > responseQueue_;

        ResponseHandlerVisitor responseHandler_;
        ResponseFactory responseFactory_;

        const uint8_t COMMAND_TYPE_POSITION = 5;
        const uint8_t COMMAND_SENDING_REPETITION = 5;

        utility::Logger& logger_;
    };

}
#endif
