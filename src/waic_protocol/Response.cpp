#include "Response.h"

using namespace std;
using namespace communication;

Response::Response(uint8_t dataSizeIn, ResponseType responseTypeIn)
        : Frame(FrameType::RESPONSE, dataSizeIn),
          responseType(responseTypeIn)
{
}

Response::~Response()
{
}

const ResponseType& Response::getResponseType()
{
    return responseType;
}
