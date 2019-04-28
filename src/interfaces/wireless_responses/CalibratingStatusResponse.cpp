#include "CalibratingStatusResponse.h"

#include "ResponseVisitor.h"
#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

CalibratingStatusResponse::CalibratingStatusResponse(CalibrationConfiguration configuration, uint8_t mode)
    : Response(10, ResponseType::CALIBRATING_STATUS),
      mode_(mode),
      calibrationConfiguration_(configuration)
{}

CalibratingStatusResponse::~CalibratingStatusResponse()
{}

vector<uint8_t> CalibratingStatusResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));
    frame.push_back(mode_);

    const auto tempFrame = BytesConverter::appendStructToVectorOfUINT8(calibrationConfiguration_);
    frame.insert(frame.end(), tempFrame.begin(), tempFrame.end());

    return frame;
}

string CalibratingStatusResponse::getName()
{
    return string("CalibratingStatusResponse");
}

CalibrationConfiguration CalibratingStatusResponse::getCalibrationConfiguration() const
{
    return calibrationConfiguration_;
}

void CalibratingStatusResponse::setCalibrationConfiguration(const CalibrationConfiguration &status)
{
    calibrationConfiguration_ = status;
}

uint8_t CalibratingStatusResponse::getMode() const noexcept
{
    return mode_;
}

void CalibratingStatusResponse::setMode(uint8_t mode) noexcept
{
    mode_ = mode;
}

void CalibratingStatusResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += sizeof(mode_);
    dataSize += sizeof(calibrationConfiguration_);

    setDataSize(dataSize);
}

void CalibratingStatusResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}
