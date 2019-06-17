#include "EthChangeStateCommand.h"
#include "EthFeederCommandVisitor.h"

using namespace std;
using namespace communication;

EthChangeStateCommand::EthChangeStateCommand(FeederStateCode feederState)
    : EthFeederCommand(10, EthCommandType::ETH_CHANGE_STATE),
      feederState_(feederState)
{}

EthChangeStateCommand::~EthChangeStateCommand()
{}

vector<uint8_t> EthChangeStateCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(feederState_));

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
    setDataSize(sizeof(commandType_) + sizeof(feederState_));
}

FeederStateCode EthChangeStateCommand::getFeederState() const
{
    return feederState_;
}

void EthChangeStateCommand::setFeederState(const FeederStateCode &feederState)
{
    feederState_ = feederState;
}
