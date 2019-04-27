#include "GUICallibrationCommand.h"

#include "GUICommandVisitor.h"
#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

GUICallibrationCommand::GUICallibrationCommand(CallibrationConfiguration configuration, uint8_t mode)
    : GUICommand(10, GUICommandType::CALIBRATION),
      mode_(mode),
      calibrationConfiguration_(configuration)
{}

GUICallibrationCommand::~GUICallibrationCommand()
{}

vector<uint8_t> GUICallibrationCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(mode_);

    const auto tempFrame = BytesConverter::appendStructToVectorOfUINT8(calibrationConfiguration_);
    frame.insert(frame.end(), tempFrame.begin(), tempFrame.end());

    return frame;
}

string GUICallibrationCommand::getName()
{
    return string("GUICallibrationCommand");
}

CallibrationConfiguration GUICallibrationCommand::getCalibrationConfiguration() const
{
    return calibrationConfiguration_;
}

void GUICallibrationCommand::setCalibrationConfiguration(const CallibrationConfiguration &status)
{
    calibrationConfiguration_ = status;
}

uint8_t GUICallibrationCommand::getMode() const noexcept
{
    return mode_;
}

void GUICallibrationCommand::setMode(uint8_t mode) noexcept
{
    mode_ = mode;
}

void GUICallibrationCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(mode_);
    dataSize += sizeof(calibrationConfiguration_);

    setDataSize(dataSize);
}

void GUICallibrationCommand::accept(GUICommandVisitor &visitor)
{
    visitor.visit(*this);
}
