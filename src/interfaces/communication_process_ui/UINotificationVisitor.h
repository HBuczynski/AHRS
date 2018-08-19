#ifndef AHRS_UINOTIFICATIONVISITOR_H
#define AHRS_UINOTIFICATIONVISITOR_H

#include "ReceivingDataNotification.h"
#include "CommunicationStatusNotification.h"

namespace communication
{
    class UINotificationVisitor
    {
    public:
        UINotificationVisitor(){};
        virtual ~UINotificationVisitor(){};

        virtual void visit(ReceivingDataNotification& command) = 0;
        virtual void visit(CommunicationStatusNotification& command) = 0;

    };
}

#endif