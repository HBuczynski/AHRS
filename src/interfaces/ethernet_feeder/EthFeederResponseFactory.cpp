#include "EthFeederResponseFactory.h"

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
        default:
            throw invalid_argument("Received command does not register in factory.");
    }
}

