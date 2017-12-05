#include "WAICEndConnectionCommand.h"

using namespace std;
using namespace communication;

WAICEndConnectionCommand::WAICEndConnectionCommand()
        : WAICCommand(10, WAICCommandType::END_CONNECTION)
{
}

WAICEndConnectionCommand::WAICEndConnectionCommand(const std::vector<uint8_t> &frameBytes)
        : WAICCommand(10, WAICCommandType::END_CONNECTION)
{
}

WAICEndConnectionCommand::~WAICEndConnectionCommand()
{

}

std::vector<uint8_t> WAICEndConnectionCommand::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();


    return frame;;
}

std::string WAICEndConnectionCommand::getName()
{
    return string("EndConnectionCommand");
}
