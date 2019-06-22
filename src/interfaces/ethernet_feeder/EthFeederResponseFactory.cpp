#include "EthFeederResponseFactory.h"

#include "EthAckFeederBuilder.h"

using namespace std;
using namespace communication;

EthFeederResponseFactory::EthFeederResponseFactory()
{}

EthFeederResponseFactory::~EthFeederResponseFactory()
{}

unique_ptr<EthFeederResponse> EthFeederResponseFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<EthResponseType >(commandInBytes[Frame::RESPONSE_TYPE_POSITION]);

    switch (type)
    {
        case EthResponseType::ETH_ACK :
            builder_ = make_unique<EthAckFeederBuilder>();
            return move(builder_->create(commandInBytes));

        default:
            throw invalid_argument("Received eth response does not register in factory.");
    }
}

