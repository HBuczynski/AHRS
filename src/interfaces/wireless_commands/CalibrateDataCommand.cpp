#include "CalibrateDataCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

CalibrateDataCommand::CalibrateDataCommand()
    : Command(10,CommandType::CALIBRATE_DATA)
{}

CalibrateDataCommand::~CalibrateDataCommand()
{}

vector<uint8_t > CalibrateDataCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string CalibrateDataCommand::getName()
{
    return string("CalibrateDataCommand");
}

void CalibrateDataCommand::accept(CommandVisitor& visitor)
{
    visitor.visit(*this);
}

void CalibrateDataCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);

    setDataSize(dataSize);
}

