#include "GUIStartAcqResponse.h"
#include "GUIResponseVisitor.h"

using namespace std;
using namespace communication;

GUIStartAcqResponse::GUIStartAcqResponse()
        : GUIResponse(10, GUIResponseType::GUI_START_ACQ)
{}

GUIStartAcqResponse::~GUIStartAcqResponse()
{}

vector<uint8_t> GUIStartAcqResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

string GUIStartAcqResponse::getName()
{
    return string("GUIStartAcqResponse");
}

void GUIStartAcqResponse::accept(GUIResponseVisitor &visitor)
{
    visitor.visit(*this);
}

void GUIStartAcqResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);

    setDataSize(dataSize);
}
