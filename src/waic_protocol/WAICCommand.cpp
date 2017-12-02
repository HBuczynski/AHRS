#include "WAICCommand.h"

using namespace std;
using namespace communication;

WAICCommand::WAICCommand(uint8_t dataSizeIn, WAICCommandType commandTypeIn)
    : WAICFrame(WAICFrameType::COMMAND, dataSizeIn),
      commandType(commandTypeIn)

{
}

WAICCommand::~WAICCommand()
{
}

const WAICCommandType& WAICCommand::getCommandType()
{
    return commandType;
}
