#ifndef ETHCOMMANDHANDLER_H
#define ETHCOMMANDHANDLER_H

#include <feeder/external_communication/ClientUDPManager.h>
#include <interfaces/ethernet_feeder/EthFeederCommandVisitor.h>
#include <interfaces/ethernet_feeder/EthFeederResponse.h>

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

        void initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager);
        void initializeCurrentClient(ClientThreadTCP *client);
        void initializeMainMsgQueue();

        std::unique_ptr<EthFeederResponse> getResponse();

    private:
        ClientThreadTCP *currentClient_;
        std::shared_ptr<ClientUDPManager> clientUDPManager_;
        std::unique_ptr<EthFeederResponse> response_;

        config::FeederMessageQueues msgQueuesParametes_;
        std::shared_ptr<MessageQueueWrapper> mainMsgQueue_;

        utility::Logger& logger_;
    };
}

#endif // ETHCOMMANDHANDLER_H
