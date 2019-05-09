#include "DatabaseNameNotification.h"
#include "UINotificationVisitor.h"

using namespace std;
using namespace communication;

DatabaseNameNotification::DatabaseNameNotification(config::UICommunicationMode mode)
    : UINotification(10, UINotificationType::DATABASE_NAME),
      mode_(mode)
{ }

DatabaseNameNotification::~DatabaseNameNotification()
{ }

vector<uint8_t> DatabaseNameNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(uiNotificationType));
    frame.push_back(static_cast<uint8_t>(mode_));

    return frame;
}

string DatabaseNameNotification::getName()
{
    return string("DatabaseNameNotification");
}


void DatabaseNameNotification::setMode(config::UICommunicationMode mode)
{
    mode_ = mode;
}

config::UICommunicationMode DatabaseNameNotification::getMode() const noexcept
{
    return mode_;
}

void DatabaseNameNotification::accept(UINotificationVisitor &visitor)
{
    visitor.visit(*this);
}

void DatabaseNameNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(uiNotificationType);
    dataSize += sizeof(mode_);

    setDataSize(dataSize);
}
