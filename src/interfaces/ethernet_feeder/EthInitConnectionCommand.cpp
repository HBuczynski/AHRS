#include "EthInitConnectionCommand.h"
#include "EthFeederCommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

EthInitConnectionCommand::EthInitConnectionCommand(uint16_t port, std::string address)
    : EthFeederCommand(10, EthCommandType::ETH_CHANGE_STATE),
      serverListenUDPPort_(port),
      serverAddress_(address)
{}

EthInitConnectionCommand::~EthInitConnectionCommand()
{}

vector<uint8_t> EthInitConnectionCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendUINT16toVectorOfUINT8(serverListenUDPPort_, frame);
    BytesConverter::appendStringToVectorOfUINT8(serverAddress_, frame);

    return frame;
}

string EthInitConnectionCommand::getName()
{
    return string("EthInitConnectionCommand");
}

void EthInitConnectionCommand::accept(EthFeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void EthInitConnectionCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += serverAddress_.size() + sizeof(END_STRING_IN_FRAME);
    dataSize += sizeof(serverListenUDPPort_);

    setDataSize(dataSize);
}

uint16_t EthInitConnectionCommand::getServerListenUDPPort() const
{
    return serverListenUDPPort_;
}

void EthInitConnectionCommand::setServerListenUDPPort(const uint16_t &serverListenUDPPort)
{
    serverListenUDPPort_ = serverListenUDPPort;
}

std::string EthInitConnectionCommand::getServerAddress() const
{
    return serverAddress_;
}

void EthInitConnectionCommand::setServerAddress(const std::string &serverAddress)
{
    serverAddress_ = serverAddress;
}
