#include "GUIShutdownResponse.h"
#include "GUIResponseVisitor.h"

using namespace std;
using namespace communication;

GUIShutdownResponse::GUIShutdownResponse()
        : GUIResponse(10, GUIResponseType::GUI_SHUTDOWN)
{}

GUIShutdownResponse::~GUIShutdownResponse()
{}

vector<uint8_t> GUIShutdownResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

string GUIShutdownResponse::getName()
{
    return string("GUIShutdownResponse");
}

void GUIShutdownResponse::accept(GUIResponseVisitor &visitor)
{
    visitor.visit(*this);
}

void GUIShutdownResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);

    setDataSize(dataSize);
}

