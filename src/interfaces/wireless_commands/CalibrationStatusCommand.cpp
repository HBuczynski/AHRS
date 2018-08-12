#include "CalibrationStatusCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

CalibrationStatusCommand::CalibrationStatusCommand()
        : Command(10, CommandType::CALIBRATION_STATUS)
{}

CalibrationStatusCommand::~CalibrationStatusCommand()
{}

vector<uint8_t> CalibrationStatusCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string CalibrationStatusCommand::getName()
{
    return string("CalibrationStatusCommand");
}

void CalibrationStatusCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void CalibrationStatusCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
