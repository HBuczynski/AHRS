#include "CalibratingStatusResponse.h"

#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

CalibratingStatusResponse::CalibratingStatusResponse(CalibrationStatus status)
    : Response(10, ResponseType::CALIBRATING_STATUS),
      status_(status)
{}

CalibratingStatusResponse::~CalibratingStatusResponse()
{}

vector<uint8_t> CalibratingStatusResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));
    frame.push_back(static_cast<uint8_t>(status_));

    return frame;
}

string CalibratingStatusResponse::getName()
{
    return string("CalibratingStatusResponse");
}

CalibrationStatus CalibratingStatusResponse::getCalibrationStatus() const
{
    return status_;
}

void CalibratingStatusResponse::setCalibrationStatus(CalibrationStatus status)
{
    status_ = status;
}

void CalibratingStatusResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += sizeof(status_);

    setDataSize(dataSize);
}

void CalibratingStatusResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}
