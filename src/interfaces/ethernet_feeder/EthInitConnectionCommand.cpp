#include "EthInitConnectionCommand.h"
#include "EthFeederCommandVisitor.h"

using namespace std;
using namespace communication;

EthInitConnectionCommand::EthInitConnectionCommand()
    : EthFeederCommand(10, EthCommandType::ETH_CHANGE_STATE)
{}

EthInitConnectionCommand::~EthInitConnectionCommand()
{}

vector<uint8_t> EthInitConnectionCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

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
    setDataSize(sizeof(commandType_));
}
