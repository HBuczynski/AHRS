#ifndef AHRS_MESSAGEQUEUEWRAPPER_H
#define AHRS_MESSAGEQUEUEWRAPPER_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include <memory>
#include <string>

namespace communication
{
    class MessageQueueWrapper
    {
    public:
        MessageQueueWrapper(std::string name);
        MessageQueueWrapper(std::string name, uint32_t  messageQueueNumber, uint32_t messageQueueSize);
        ~MessageQueueWrapper();

        void send(std::vector<uint8_t>& msg);
        std::vector<uint8_t> receive();

    private:
        void checksum(std::vector<uint8_t> &msg);

        std::shared_ptr<boost::interprocess::message_queue> receivingMessageQueue_;

    };
}

#endif