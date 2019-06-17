#include "EthAckFeederBuilder.h"

#include "EthAckFeederResponse.h"

using namespace std;
using namespace communication;

std::unique_ptr<EthFeederResponse> EthAckFeederBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<EthAckFeederResponse>();

    return move(command);
}
