#include "EthAckFeederResponse.h"
#include "EthFeederResponseVisitor.h"

using namespace std;
using namespace communication;

EthAckFeederResponse::EthAckFeederResponse()
    : EthFeederResponse(10, EthResponseType::ETH_ACK)
{}

EthAckFeederResponse::~EthAckFeederResponse()
{}

vector<uint8_t> EthAckFeederResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

string EthAckFeederResponse::getName()
{
    return string("EthAckFeederResponse");
}

void EthAckFeederResponse::accept(EthFeederResponseVisitor &visitor)
{
    visitor.visit(*this);
}

void EthAckFeederResponse::initializeDataSize()
{
    setDataSize(sizeof(responseType_));
}
