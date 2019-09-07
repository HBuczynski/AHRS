#include "GUIRestartResponse.h"
#include "GUIResponseVisitor.h"

using namespace std;
using namespace communication;

GUIRestartResponse::GUIRestartResponse()
        : GUIResponse(10, GUIResponseType::GUI_RESTART)
{}

GUIRestartResponse::~GUIRestartResponse()
{}

vector<uint8_t> GUIRestartResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

string GUIRestartResponse::getName()
{
    return string("GUIRestartResponse");
}

void GUIRestartResponse::accept(GUIResponseVisitor &visitor)
{
    visitor.visit(*this);
}

void GUIRestartResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);

    setDataSize(dataSize);
}

