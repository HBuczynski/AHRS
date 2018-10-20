#include "BITsResponse.h"
#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

BITsResponse::BITsResponse(uint8_t state, config::UICommunicationMode systemMode)
        : Response(10, ResponseType::BITs_STATUS),
          state_(state),
          systemMode_(systemMode)
{ }

BITsResponse::~BITsResponse()
{ }

vector<uint8_t> BITsResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));
    frame.push_back(state_);
    frame.push_back(static_cast<uint8_t>(systemMode_));

    return frame;
}

string BITsResponse::getName()
{
    return string("BITsResponse");
}

void BITsResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}

uint8_t BITsResponse::getState() const
{
    return state_;
}

void BITsResponse::setState(uint8_t state)
{
    state_ = state;
}

config::UICommunicationMode BITsResponse::getSystemMode() const
{
    return systemMode_;
}

void BITsResponse::setSystemMode(config::UICommunicationMode systemMode)
{
    systemMode_ = systemMode;
}

void BITsResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += sizeof(systemMode_);
    dataSize += sizeof(state_);

    setDataSize(dataSize);
}
