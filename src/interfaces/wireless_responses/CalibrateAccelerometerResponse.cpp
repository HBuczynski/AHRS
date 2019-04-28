#include "CalibrateAccelerometerResponse.h"

#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

CalibrateAccelerometerResponse::CalibrateAccelerometerResponse(AccelActionResponse status)
    : Response(10, ResponseType::ACCEL_STATUS),
      status_(status)
{}

CalibrateAccelerometerResponse::~CalibrateAccelerometerResponse()
{}

vector<uint8_t > CalibrateAccelerometerResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));
    frame.push_back(static_cast<uint8_t>(status_));

    return frame;
}

string CalibrateAccelerometerResponse::getName()
{
    return string("CalibrateAccelerometerResponse");
}

void CalibrateAccelerometerResponse::accept(ResponseVisitor& visitor)
{
    visitor.visit(*this);
}

void CalibrateAccelerometerResponse::setActionResponse(AccelActionResponse status) noexcept
{
    status_ = status;
}

AccelActionResponse CalibrateAccelerometerResponse::getActionResponse() const noexcept
{
    return status_;
}

void CalibrateAccelerometerResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += sizeof(status_);

    setDataSize(dataSize);
}
