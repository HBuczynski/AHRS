#include "StartAcquisitionCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;
using namespace communication;

StartAcquisitionCommand::StartAcquisitionCommand()
        : Command(10, CommandType::START_ACQ)
{}

StartAcquisitionCommand::~StartAcquisitionCommand()
{}

vector<uint8_t> StartAcquisitionCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string StartAcquisitionCommand::getName()
{
    return string("StartAcquisitionCommand");
}

void StartAcquisitionCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void StartAcquisitionCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
