#include "FMRestartChangeMasterCommand.h"
#include "FMCommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace communication;

FMRestartChangeMasterCommand::FMRestartChangeMasterCommand(string systemState)
        : FMCommand(10, FMCommandType::RESTART_MASTER_WITH_CHANGE),
          systemState_(systemState)
{ }

FMRestartChangeMasterCommand::~FMRestartChangeMasterCommand()
{ }

vector<uint8_t> FMRestartChangeMasterCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    utility::BytesConverter::appendStringToVectorOfUINT8(systemState_, frame);

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
    dataSize += systemState_.size() + sizeof(END_STRING_IN_FRAME);

    setDataSize(dataSize);
}

std::string FMRestartChangeMasterCommand::getSystemState() const
{
    return systemState_;
}

void FMRestartChangeMasterCommand::setSystemState(const std::string &systemState)
{
    systemState_ = systemState;
}
