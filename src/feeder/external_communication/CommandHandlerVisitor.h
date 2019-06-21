#ifndef AHRS_BLACK_BOX_COMMANDHANDLER_H
#define AHRS_BLACK_BOX_COMMANDHANDLER_H

#include <feeder/external_communication/ClientUDPManager.h>
#include <interfaces/wireless_commands/CommandVisitor.h>
#include <interfaces/wireless_responses/Response.h>

#include "FlightDataManager.h"
    #include <config_reader/FeederParameters.h>
    #include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <logger/Logger.h>
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
        virtual void visit(CalibrateAccelerometerCommand& command) override;
        virtual void visit(CalibrateDataCommand& command) override;
        virtual void visit(BITSDataCommand& command) override;
        virtual void visit(StopAcqCommand& command) override;
        virtual void visit(SetHashCommand& command) override;
        virtual void visit(UDPBitsCommand& command) override;
        virtual void visit(HandshakeCommand& command) override;
        virtual void visit(ChangeStateCommand& command) override;

        void initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager);
        void initializeExternalSharedMemory();
        void initializeCurrentClient(ClientThreadTCP *client);

        std::unique_ptr<Response> getResponse();
        void stopAcq();

    private:
        std::string getPlanesDataset();
        void runAcq();

        std::atomic<bool> runAcquisition_;
        std::thread acquisitionThread_;

        ClientThreadTCP *currentClient_;
        std::shared_ptr<ClientUDPManager> clientUDPManager_;
        std::unique_ptr<Response> response_;

        config::FeederSharedMemory sharedMemoryParameters_;
        std::unique_ptr<communication::SharedMemoryWrapper> externalSharedMemory_;

        utility::Logger& logger_;
    };
}
#endif
