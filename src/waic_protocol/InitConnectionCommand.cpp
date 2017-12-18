#include "InitConnectionCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

//TO DO: add data size
InitConnectionCommand::InitConnectionCommand(uint16_t port, std::string addres)
        : Command(10, CommandType::INIT_CONNECTION),
          serverListenUDPPort_(port),
          serverAddress_(addres)
{
}

InitConnectionCommand::~InitConnectionCommand()
{
}

vector<uint8_t> InitConnectionCommand::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();



    return frame;
}

string InitConnectionCommand::getName()
{
    return string("InitConnectionCommand");
}

uint16_t InitConnectionCommand::getPort()
{
    return  serverListenUDPPort_;
}

string InitConnectionCommand::getAddress()
{
    return serverAddress_;
}

void InitConnectionCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}


