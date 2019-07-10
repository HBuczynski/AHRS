#include "FMRestartChangeMasterCommand.h"
#include "FMCommandVisitor.h"

using namespace std;
using namespace communication;

FMRestartChangeMasterCommand::FMRestartChangeMasterCommand()
        : FMCommand(10, FMCommandType::RESTART_MASTER_WITH_CHANGE)
{ }

FMRestartChangeMasterCommand::~FMRestartChangeMasterCommand()
{ }

vector<uint8_t> FMRestartChangeMasterCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string FMRestartChangeMasterCommand::getName()
{
    return string("HMRestartChangeMasterCommand");
}

void FMRestartChangeMasterCommand::accept(FMCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void FMRestartChangeMasterCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);

    setDataSize(dataSize);
}
