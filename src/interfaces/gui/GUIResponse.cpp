#include "GUIResponse.h"

using namespace std;
using namespace communication;

GUIResponse::GUIResponse(uint8_t dataSizeIn, GUIResponseType responseTypeIn)
        : Frame(FrameType::RESPONSE, InterfaceType::GUI, dataSizeIn),
          responseType_(responseTypeIn)
{}

GUIResponse::~GUIResponse()
{}

const GUIResponseType& GUIResponse::getResponseType() const
{
    return responseType_;
}
