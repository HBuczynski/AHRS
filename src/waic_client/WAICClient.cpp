#include "WAICClient.h"

using namespace std;
using namespace communication;

WAICClient::WAICClient(uint16_t portIn, string addressIn)
    : port_(portIn),
      address_(addressIn)
{
    datagram = make_shared<WAICDatagramUDP>(CLIENT, port_, address_);
}

WAICClient::~WAICClient()
{

}

void WAICClient::sendData(std::string message)
{
    datagram->sendPacket(message);
}
