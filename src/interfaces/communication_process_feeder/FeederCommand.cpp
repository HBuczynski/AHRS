#include "FeederCommand.h"

using namespace std;
using namespace communication;

FeederCommand::FeederCommand(uint8_t dataSizeIn, FeederCommandType commandTypeIn)
        : Frame(FrameType::COMMAND, InterfaceType::COMMUNICATION_PROCESS_FEEDER, dataSizeIn),
          commandType_(commandTypeIn)
{}

FeederCommand::~FeederCommand()
{}

const FeederCommandType &FeederCommand::getCommandType() const
{
    return commandType_;
}
