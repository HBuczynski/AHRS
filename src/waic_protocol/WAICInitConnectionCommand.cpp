#include "WAICInitConnectionCommand.h"

using namespace std;
using namespace communication;

//TO DO: add data size
WAICInitConnectionCommand::WAICInitConnectionCommand()
        : WAICCommand(10, WAICCommandType::INIT_CONNECTION)
{
}

WAICInitConnectionCommand::WAICInitConnectionCommand(const vector<uint8_t> &frameBytes)
        : WAICCommand(10, WAICCommandType::INIT_CONNECTION)
{

}

WAICInitConnectionCommand::~WAICInitConnectionCommand()
{
}

vector<uint8_t> WAICInitConnectionCommand::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();



    return frame;
}

string WAICInitConnectionCommand::getName()
{
    return string("InitConnectionCommand");
}

uint16_t WAICInitConnectionCommand::getPort()
{
    return  serverListenUDPPort_;
}

string WAICInitConnectionCommand::getAddress()
{
    return serverAddress_;
}


