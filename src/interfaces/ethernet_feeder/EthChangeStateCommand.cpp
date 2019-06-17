#include "EthChangeStateCommand.h"
#include "EthFeederCommandVisitor.h"

using namespace std;
using namespace communication;

EthChangeStateCommand::EthChangeStateCommand()
    : EthFeederCommand(10, EthCommandType::ETH_CHANGE_STATE)
{}

EthChangeStateCommand::~EthChangeStateCommand()
{}

vector<uint8_t> EthChangeStateCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string EthChangeStateCommand::getName()
{
    return string("EthChangeStateCommand");
}

void EthChangeStateCommand::accept(EthFeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void EthChangeStateCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
