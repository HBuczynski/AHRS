#include "ClientUDP.h"

using namespace std;
using namespace communication;

ClientUDP::ClientUDP(uint16_t portIn, string addressIn)
    : port_(portIn),
      address_(addressIn)
{
    datagram_ = make_unique<SendDatagramUDP>(port_, address_);
}

ClientUDP::~ClientUDP()
{
}

void ClientUDP::sendData(std::vector<uint8_t> &message)
{
    datagram_->sendData(message);
}
