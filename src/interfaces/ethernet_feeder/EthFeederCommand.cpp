#include "EthFeederCommand.h"

using namespace std;
using namespace communication;

EthFeederCommand::EthFeederCommand(uint8_t dataSizeIn, EthCommandType ethCommandTypeIn)
    : Frame(FrameType::COMMAND, InterfaceType::WIRELESS, dataSizeIn),
      commandType_(ethCommandTypeIn)

{}

EthFeederCommand::~EthFeederCommand()
{}

const EthCommandType& EthFeederCommand::getCommandType() const
{
    return commandType_;
}
