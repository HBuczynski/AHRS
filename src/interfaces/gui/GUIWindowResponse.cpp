#include "GUIWindowResponse.h"

#include "GUIResponseVisitor.h"

using namespace std;;
using namespace communication;

GUIWindowResponse::GUIWindowResponse(PagesType pageType)
        : GUIResponse(10, GUIResponseType::WINDOWS_TYPE),
          pageType_(pageType)
{}

GUIWindowResponse::~GUIWindowResponse()
{}

vector<uint8_t> GUIWindowResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));
    frame.push_back(static_cast<uint8_t>(pageType_));

    return frame;
}

string GUIWindowResponse::getName()
{
    return string("GUIWindowResponse");
}

void GUIWindowResponse::accept(GUIResponseVisitor &visitor)
{
    visitor.visit(*this);
}

PagesType GUIWindowResponse::getPageType() const
{
    return pageType_;
}

void GUIWindowResponse::setPageType(PagesType pageType)
{
    pageType_ = pageType;
}

void GUIWindowResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += sizeof(pageType_);

    setDataSize(dataSize);
}
