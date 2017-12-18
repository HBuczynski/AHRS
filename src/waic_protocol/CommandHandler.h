#ifndef AHRS_BLACK_BOX_COMMANDHANDLER_H
#define AHRS_BLACK_BOX_COMMANDHANDLER_H

#include "CommandVisitor.h"
#include "Response.h"

#include <memory>
#include <waic_communication_manager/CallbackFunctions.h>

namespace communication
{
    class ClientThreadTCP;

    class CommandHandler final : public CommandVisitor
    {
    public:
        CommandHandler();
        ~CommandHandler();

        void initializeCurrentClient(ClientThreadTCP *client);
        void initializeCallbackFunction(CallbackFunctions callbackFunctions);

        virtual void visit(InitConnectionCommand& command) override;
        virtual void visit(EndConnectionCommand& command) override;

        std::shared_ptr<Response> getResponse();

    private:
        ClientThreadTCP *currentClient_;
        CallbackFunctions callbackFunctions_;

        std::shared_ptr<Response> response_;
    };
}
#endif
