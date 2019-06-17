#include "EthHandshakeCommand.h"
#include "EthFeederCommandVisitor.h"

using namespace std;
using namespace communication;

EthHandshakeCommand::EthHandshakeCommand()
    : EthFeederCommand(10, EthCommandType::ETH_CHANGE_STATE)
{}

EthHandshakeCommand::~EthHandshakeCommand()
{}

vector<uint8_t> EthHandshakeCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string EthHandshakeCommand::getName()
{
    return string("EthHandshakeCommand");
}

void EthHandshakeCommand::accept(EthFeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void EthHandshakeCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
