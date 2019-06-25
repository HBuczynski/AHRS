#include "GUIPlaneResponse.h"
#include <utility/BytesConverter.h>

#include "GUIResponseVisitor.h"

using namespace std;
using namespace utility;
using namespace communication;

GUIPlaneResponse::GUIPlaneResponse(config::UICommunicationMode mode, const std::string& plane)
        : GUIResponse(10, GUIResponseType::SET_PLANE),
          mode_(mode),
          plane_(plane)
{}

GUIPlaneResponse::~GUIPlaneResponse()
{}

vector<uint8_t> GUIPlaneResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));
    frame.push_back(static_cast<uint8_t>(mode_));
    BytesConverter::appendStringToVectorOfUINT8(plane_, frame);;

    return frame;
}

string GUIPlaneResponse::getName()
{
    return string("GUIPlaneResponse");
}

const string& GUIPlaneResponse::getPlane() const
{
    return plane_;
}

void GUIPlaneResponse::setPlane(const std::string& plane)
{
    plane_ = plane;
}

void GUIPlaneResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_) + sizeof(mode_);
    dataSize += plane_.size() + sizeof(END_STRING_IN_FRAME);

    setDataSize(dataSize);
}

config::UICommunicationMode GUIPlaneResponse::getMode() const
{
    return mode_;
}

void GUIPlaneResponse::setMode(const config::UICommunicationMode &mode)
{
    mode_ = mode;
}

void GUIPlaneResponse::accept(GUIResponseVisitor &visitor)
{
    visitor.visit(*this);
}
