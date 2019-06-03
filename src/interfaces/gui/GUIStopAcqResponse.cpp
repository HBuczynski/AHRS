#include "GUIStopAcqResponse.h"
#include "GUIResponseVisitor.h"

using namespace std;
using namespace communication;

GUIStopAcqResponse::GUIStopAcqResponse()
        : GUIResponse(10, GUIResponseType::GUI_STOP_ACQ)
{}

GUIStopAcqResponse::~GUIStopAcqResponse()
{}

vector<uint8_t> GUIStopAcqResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

string GUIStopAcqResponse::getName()
{
    return string("GUIStopAcqResponse");
}

void GUIStopAcqResponse::accept(GUIResponseVisitor &visitor)
{
    visitor.visit(*this);
}

void GUIStopAcqResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);

    setDataSize(dataSize);
}
