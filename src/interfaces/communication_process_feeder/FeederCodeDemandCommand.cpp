#include "FeederCodeDemandCommand.h"
#include "FeederCommandVisitor.h"

using namespace std;
using namespace communication;

FeederCodeDemandCommand::FeederCodeDemandCommand(FeederStateCode code)
        : FeederCommand(10, FeederCommandType::FEEDER_CODE_DEMAND),
          code_(code)
{ }

FeederCodeDemandCommand::~FeederCodeDemandCommand()
{ }

vector<uint8_t> FeederCodeDemandCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(code_));

    return frame;
}

string FeederCodeDemandCommand::getName()
{
    return string("FeederCodeDemandCommand");
}

void FeederCodeDemandCommand::accept(FeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}

FeederStateCode FeederCodeDemandCommand::getStateCode() const
{
    return code_;
}

void FeederCodeDemandCommand::setAckType(FeederStateCode code)
{
    code = code_;
}

void FeederCodeDemandCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(code_);

    setDataSize(dataSize);
}
