#include "StopAcqCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;
using namespace communication;

StopAcqCommand::StopAcqCommand()
        : Command(10, CommandType::STOP_ACQ)
{}

StopAcqCommand::~StopAcqCommand()
{}

vector<uint8_t> StopAcqCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string StopAcqCommand::getName()
{
    return string("StopAcqCommand");
}

void StopAcqCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void StopAcqCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}

