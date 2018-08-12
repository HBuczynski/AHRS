#include "CurrentStateResponse.h"
#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

CurrentStateResponse::CurrentStateResponse(StateCode code)
        : Response(10, ResponseType::CURRENT_STATE_RES),
          code_(code)
{ }

CurrentStateResponse::~CurrentStateResponse()
{ }

vector<uint8_t> CurrentStateResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));
    frame.push_back(static_cast<uint8_t>(code_));

    return frame;
}

string CurrentStateResponse::getName()
{
    return string("CurrentStateResponse");
}

void CurrentStateResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}

StateCode CurrentStateResponse::getStateCode() const
{
    return code_;
}

void CurrentStateResponse::setAckType(StateCode code)
{
    code = code_;
}

void CurrentStateResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += sizeof(code_);

    setDataSize(dataSize);
}
