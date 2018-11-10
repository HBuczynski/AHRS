#include <utility/BytesConverter.h>
#include <checksum/Checksum.h>

#include "MessageQueueWrapper.h"


using namespace std;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

MessageQueueWrapper::MessageQueueWrapper(string name, uint32_t messageQueueSize)
    :   name_(name),
        messageQueueNumber_(0),
        messageQueueSize_(messageQueueSize)
{
    messageQueue_ = make_shared<message_queue>(open_only, name_.c_str());
}

MessageQueueWrapper::MessageQueueWrapper(string name, uint32_t messageQueueNumber, uint32_t messageQueueSize)
    :   name_(name),
        messageQueueNumber_(messageQueueNumber),
        messageQueueSize_(messageQueueSize)
{
    message_queue::remove(name.c_str());
    messageQueue_ = make_shared<message_queue>(create_only, name.c_str(),
                            messageQueueNumber,
                            messageQueueSize);
}

MessageQueueWrapper::~MessageQueueWrapper()
{}

void MessageQueueWrapper::send(vector<uint8_t> &msg)
{
    auto parityBit = Checksum::parityBit(msg);
    const auto crc32 = Checksum::crc32(msg);

    msg.push_back(parityBit);
    BytesConverter::appendUINT32toVectorOfUINT8(crc32, msg);

    messageQueue_->send(msg.data(), msg.size(), 0);
}

vector<uint8_t> MessageQueueWrapper::receive()
{
    unsigned int priority;
    message_queue::size_type receivedSize;

    vector<uint8_t> packet(messageQueueSize_);
   // fill(packet.begin(), packet.end(), 0);

    messageQueue_->receive(packet.data(), packet.size(), receivedSize, priority);

    packet.resize(receivedSize);
    packet.shrink_to_fit();
    checksum(packet);

    return packet;
}

void MessageQueueWrapper::checksum(vector<uint8_t> &msg)
{
    const auto crcFromFrame = BytesConverter::fromVectorOfUINT8toUINT32(msg, msg.size() - sizeof(uint32_t));
    const auto parityFromFrame = msg[msg.size() - sizeof(uint32_t) - sizeof(uint8_t)];

    const auto commandFrame = vector<uint8_t>(msg.begin(), msg.begin() + msg.size() - sizeof(uint8_t) - sizeof(uint32_t));
    const auto parityBit = Checksum::parityBit(commandFrame);
    const auto crc32 = Checksum::crc32(commandFrame);

    if(crcFromFrame != crc32 || parityFromFrame != parityBit)
    {
        throw logic_error("Checksum is incorrect.");
    }
}
