#include "EthFeederResponse.h"

using namespace std;
using namespace communication;

EthFeederResponse::EthFeederResponse(uint8_t dataSizeIn, EthResponseType responseTypeIn)
        : Frame(FrameType::RESPONSE, InterfaceType::ETHERNET_FEEDER, dataSizeIn),
          responseType_(responseTypeIn)
{}

EthFeederResponse::~EthFeederResponse()
{}

const EthResponseType& EthFeederResponse::getResponseType() const
{
    return responseType_;
}
