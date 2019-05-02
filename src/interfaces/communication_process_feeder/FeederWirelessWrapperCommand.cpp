#include "FeederWirelessWrapperCommand.h"
#include "FeederCommandVisitor.h"

using namespace std;
using namespace communication;

FeederWirelessWrapperCommand::FeederWirelessWrapperCommand(const vector<uint8_t> &data)
    : FeederCommand(10, FeederCommandType::COMMAND_WRAPPER),
      data_(data)
{}

FeederWirelessWrapperCommand::~FeederWirelessWrapperCommand()
{}

vector<uint8_t> FeederWirelessWrapperCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.insert(frame.end(), data_.begin(), data_.end());

    return frame;
}

string FeederWirelessWrapperCommand::getName()
{
    return string("GUIWirelessComWrapperCmmand");
}

void FeederWirelessWrapperCommand::accept(FeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}

const vector<uint8_t> &FeederWirelessWrapperCommand::getDataFrame() const
{
    return data_;
}

void FeederWirelessWrapperCommand::setDataFrame(const vector<uint8_t> &data)
{
    data_ = data;
}

void FeederWirelessWrapperCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += data_.size();

    setDataSize(dataSize);
}

