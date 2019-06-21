#include "FeederStateCodeResponse.h"
#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

FeederStateCodeResponse::FeederStateCodeResponse(FeederStateCode code)
        : Response(10, ResponseType::FEEDER_STATE_CODE_RES),
          code_(code)
{ }

FeederStateCodeResponse::~FeederStateCodeResponse()
{ }

vector<uint8_t> FeederStateCodeResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));
    frame.push_back(static_cast<uint8_t>(code_));

    return frame;
}

string FeederStateCodeResponse::getName()
{
    return string("FeederStateCodeResponse");
}

void FeederStateCodeResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}

FeederStateCode FeederStateCodeResponse::getStateCode() const
{
    return code_;
}

void FeederStateCodeResponse::setAckType(FeederStateCode code)
{
    code = code_;
}

void FeederStateCodeResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += sizeof(code_);

    setDataSize(dataSize);
}
