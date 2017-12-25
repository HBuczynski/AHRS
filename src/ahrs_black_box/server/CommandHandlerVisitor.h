#ifndef AHRS_BLACK_BOX_COMMANDHANDLER_H
#define AHRS_BLACK_BOX_COMMANDHANDLER_H

#include <ahrs_black_box/communication_manager/ClientUDPManager.h>
#include <protocol/CommandVisitor.h>
#include <protocol/Response.h>

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

        void initializeClientUDPManager(ClientUDPManager* clientUDPManager);
        void initializeCurrentClient(ClientThreadTCP *client);

        std::unique_ptr<Response> getResponse();

    private:
        ClientThreadTCP *currentClient_;
        ClientUDPManager *clientUDPManager_;

        std::unique_ptr<Response> response_;
    };
}
#endif
