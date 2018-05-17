#ifndef AHRS_BLACK_BOX_COMMANDHANDLER_H
#define AHRS_BLACK_BOX_COMMANDHANDLER_H

#include <feeder/server_tcp/ClientUDPManager.h>
#include <logger/Logger.h>
#include <interfaces/wireless_commands/CommandVisitor.h>
#include <interfaces/wireless_responses/Response.h>

#include <memory>

namespace communication
{
    class ClientThreadTCP;

    class CommandHandlerVisitor final : public CommandVisitor
    {
    public:
        CommandHandlerVisitor();
        ~CommandHandlerVisitor();

        virtual void visit(InitConnectionCommand& command) override;
        virtual void visit(EndConnectionCommand& command) override;
        virtual void visit(CallibrateMagnetometerCommand& command) override;
        virtual void visit(CollectDataCommand& command) override;
        virtual void visit(SetPlaneMagnetometerCommand& command) override;

        void initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager);
        void initializeCurrentClient(ClientThreadTCP *client);

        std::unique_ptr<Response> getResponse();

    private:
        ClientThreadTCP *currentClient_;
        std::shared_ptr<ClientUDPManager> clientUDPManager_;

        std::unique_ptr<Response> response_;

        utility::Logger& logger_;
    };
}
#endif
