#include "Client.h"

using namespace std;
using namespace communication;

Client::Client(uint16_t portIn, string addressIn)
    : port_(portIn),
      address_(addressIn)
{
    datagram_ = make_unique<SendDatagramUDP>(port_, address_);
}

Client::~Client()
{
}

void Client::sendData(std::vector<uint8_t> &message)
{
    datagram_->sendData(message);
}
