#ifndef AHRS_BLACK_BOX_COMMANDHANDLER_H
#define AHRS_BLACK_BOX_COMMANDHANDLER_H

#include <feeder/external_communication/ClientUDPManager.h>
#include <logger/Logger.h>
#include <interfaces/wireless_commands/CommandVisitor.h>
#include <interfaces/wireless_responses/Response.h>

#include <boost/interprocess/ipc/message_queue.hpp>

#include <config_reader/FeederParameters.h>
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
        virtual void visit(CalibrationStatusCommand& command) override;
        virtual void visit(StartAcquisitionCommand& command) override;
        virtual void visit(CollectDataCommand& command) override;
        virtual void visit(SetPlaneCommand& command) override;
        virtual void visit(RemovePlaneDataCommand& command) override;
        virtual void visit(CurrentStateCommand& command) override ;
        virtual void visit(PerformBITsCommand& command) override;


        void initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager);
        void initializeCurrentClient(ClientThreadTCP *client);

        std::unique_ptr<Response> getResponse();

    private:
        std::string getPlanesDataset();

        ClientThreadTCP *currentClient_;
        std::shared_ptr<ClientUDPManager> clientUDPManager_;

        std::unique_ptr<Response> response_;

        utility::Logger& logger_;
    };
}
#endif
