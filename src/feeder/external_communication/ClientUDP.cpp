#include "ClientUDP.h"

using namespace std;
using namespace utility;
using namespace communication;

ClientUDP::ClientUDP(uint16_t portIn, string addressIn)
    : port_(portIn),
      address_(addressIn),
      logger_(Logger::getInstance())
{
    datagram_ = make_unique<SendDatagramUDP>(port_, address_);
}

ClientUDP::~ClientUDP()
{
}

void ClientUDP::sendData(std::vector<uint8_t> &frame)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("ClientUDP :: Client send data to address: ") + address_ + string(" and port: ") +
                         to_string(port_) + string(".");

        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    try
    {
        datagram_->sendData(frame);
    }
    catch (exception &e)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("ClientUDP :: Client cannot send data to address: ") + address_ + string(" and port: ") +
                                   to_string(port_) + string(".");

            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}
