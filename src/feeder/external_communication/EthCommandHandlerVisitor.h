#ifndef ETHCOMMANDHANDLER_H
#define ETHCOMMANDHANDLER_H

#include <feeder/external_communication/ClientUDPManager.h>
#include <interfaces/ethernet_feeder/EthFeederCommandVisitor.h>
#include <interfaces/ethernet_feeder/EthFeederResponse.h>

#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <config_reader/FeederParameters.h>

namespace communication
{
    class ClientThreadTCP;

    class EthCommandHandlerVisitor final : public EthFeederCommandVisitor
    {
    public:
        EthCommandHandlerVisitor();
        ~EthCommandHandlerVisitor();

        void visit(EthChangeStateCommand& command) override;
        void visit(EthHandshakeCommand& command) override;
        void visit(EthInitConnectionCommand& command) override;
        void visit(EthKeepAliveCommand& command) override;

        void initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager);
        void initializeCurrentClient(ClientThreadTCP *client);
        void initializeSharedMemory();

        std::unique_ptr<EthFeederResponse> getResponse();

    private:
        void startDataSending();
        void stopDataSending();

        ClientThreadTCP *currentClient_;
        std::unique_ptr<ClientUDP> clientUDP_;
        std::shared_ptr<ClientUDPManager> clientUDPManager_;
        std::unique_ptr<EthFeederResponse> response_;

        std::atomic<bool> runAcq_;
        std::thread acqThread_;

        config::FeederSharedMemory sharedMemoryParameters_;
        std::unique_ptr<communication::SharedMemoryWrapper> internalSharedMemory_;

        utility::Logger& logger_;
    };
}

#endif // ETHCOMMANDHANDLER_H
