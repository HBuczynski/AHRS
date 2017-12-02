#include "WAICResponse.h"

using namespace std;
using namespace communication;

WAICResponse::WAICResponse(uint8_t dataSizeIn, WAICResponseType responseTypeIn)
        : WAICFrame(WAICFrameType::RESPONSE, dataSizeIn),
          responseType(responseTypeIn)
{
}

WAICResponse::~WAICResponse()
{
}

const WAICResponseType& WAICResponse::getResponseType()
{
    return responseType;
}
