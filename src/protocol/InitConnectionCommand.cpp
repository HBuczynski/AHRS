#include "InitConnectionCommand.h"
#include "CommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;


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
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendUINT16toVectorOfUINT8(serverListenUDPPort_, frame);
    vector<uint8_t > address(serverAddress_.begin(), serverAddress_.end());
    frame.insert(frame.end(), address.begin(), address.end());

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

void InitConnectionCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += serverAddress_.size();
    dataSize +=sizeof(serverListenUDPPort_);

    setDataSize(dataSize);;
}


