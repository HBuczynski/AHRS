#include "EthFeederCommandFactory.h"

#include "EthHandshakeBuilder.h"
#include "EthChangeStateBuilder.h"
#include "EthInitConnectionBuilder.h"
#include "EthKeepAliveBuilder.h"

using namespace std;
using namespace communication;

EthFeederCommandFactory::EthFeederCommandFactory()
{}

EthFeederCommandFactory::~EthFeederCommandFactory()
{}

unique_ptr<EthFeederCommand> EthFeederCommandFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<EthCommandType>(commandInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case EthCommandType::ETH_CHANGE_STATE :
            builder_ = make_unique<EthChangeStateBuilder>();
            return move(builder_->create(commandInBytes));

        case EthCommandType::ETH_HANDSHAKE :
            builder_ = make_unique<EthHandshakeBuilder>();
            return move(builder_->create(commandInBytes));

        case EthCommandType::ETH_INIT_CONNECTION :
            builder_ = make_unique<EthInitConnectionBuilder>();
            return move(builder_->create(commandInBytes));

        case EthCommandType::ETH_KEEP_ALIVE :
            builder_ = make_unique<EthKeepAliveBuilder>();
            return move(builder_->create(commandInBytes));

        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
