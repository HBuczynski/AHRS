#include "SendingDataCommand.h"
#include "UICommandVisitor.h"

using namespace std;
using namespace communication;

SendingDataCommand::SendingDataCommand(const vector<uint8_t> &data)
    : UICommand(10, UICommandType::SEND_FRAME),
      data_(data)
{}

SendingDataCommand::~SendingDataCommand()
{}

vector<uint8_t> SendingDataCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.insert(frame.end(), data_.begin(), data_.end());

    return frame;
}

string SendingDataCommand::getName()
{
    return string("SendingDataCommand");
}

void SendingDataCommand::accept(UICommandVisitor &visitor)
{
    visitor.visit(*this);
}

const vector<uint8_t> &SendingDataCommand::getDataFrame() const
{
    return data_;
}

void SendingDataCommand::setDataFrame(const vector<uint8_t> &data)
{
    data_ = data;
}

void SendingDataCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += data_.size();

    setDataSize(dataSize);
}
