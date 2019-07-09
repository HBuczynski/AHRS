#include "FMCommand.h"

using namespace std;
using namespace communication;

FMCommand::FMCommand(uint8_t dataSizeIn, FMCommandType notificationTypeIn)
        : Frame(FrameType::COMMAND, InterfaceType::FM, dataSizeIn),
          commandType_(notificationTypeIn)
{}

FMCommand::~FMCommand()
{}

const FMCommandType &FMCommand::getCommandType() const
{
    return commandType_;
}
