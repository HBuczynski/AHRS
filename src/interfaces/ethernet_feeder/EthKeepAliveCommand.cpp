#include "EthKeepAliveCommand.h"
#include "EthFeederCommandVisitor.h"

using namespace std;
using namespace communication;

EthKeepAliveCommand::EthKeepAliveCommand()
        : EthFeederCommand(10, EthCommandType::ETH_KEEP_ALIVE)
{}

EthKeepAliveCommand::~EthKeepAliveCommand()
{}

vector<uint8_t> EthKeepAliveCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string EthKeepAliveCommand::getName()
{
    return string("EthKeepAliveCommand");
}

void EthKeepAliveCommand::accept(EthFeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void EthKeepAliveCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
