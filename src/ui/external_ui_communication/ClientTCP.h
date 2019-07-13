#ifndef AHRS_BLACK_BOX_WAIC_CLIENT_H
#define AHRS_BLACK_BOX_WAIC_CLIENT_H

#include <atomic>
#include <queue>
#include <thread>
#include <mutex>

#include <functional>
#include <logger/Logger.h>
#include <packet/SendStreamTCP.h>
#include <interfaces/wireless_commands/Command.h>
#include <interfaces/wireless_responses/ResponseFactory.h>

#include <time_manager/TimerInterrupt.h>
#include "ResponseHandlerVisitor.h"

namespace communication
{
    class ClientTCP final : public utility::TimerInterruptNotification
    {
    public:
        ClientTCP(uint16_t portIn, std::string addressIn, config::UICommunicationMode mode);
        ~ClientTCP();

        void registerCallbackToHMProc(std::function<void(std::vector<uint8_t>&)> callback);
        bool connectToServer();

        void stopCommandSending();
        void startCommandSending();

        void sendCommand(std::unique_ptr<Command> command);

        void setMode(config::UICommunicationMode mode);

    private:
        bool isCommandQueueEmpty();
        std::unique_ptr<Command> getFromCommandQueue();

        void executeCommands();
        void catchExceptions(std::string exception, bool isEndConnectionSent, uint8_t commandSendingCounter);

        void interruptNotification(timer_t timerID);

        uint16_t port_;
        std::string address_;

        std::unique_ptr<SendStreamTCP> socket_;

        std::atomic<bool> executeCommandsFlag_;
        std::thread executeCommandThread_;
        config::UICommunicationMode mode_;

        std::mutex commandQueueMutex_;
        std::queue<std::unique_ptr<Command>> commandQueue_;

        ResponseHandlerVisitor responseHandler_;
        ResponseFactory responseFactory_;

        utility::TimerInterrupt keepAliveTimer_;
        const uint8_t COMMAND_SENDING_REPETITION = 3;
        const uint16_t KEEP_ALIVE_INTERVAL_MS = 1000;

        std::function<void(std::vector<uint8_t>&)> hmProcCallback_;

        utility::Logger& logger_;
    };

}
#endif
