#ifndef AHRS_FEEDERNOTIFICATIONVISITOR_H
#define AHRS_FEEDERNOTIFICATIONVISITOR_H

#include "HMHeartbeatNotification.h"
#include "HMRegisterNotification.h"
#include "HMRegisterMainNotification.h"
#include "HMErrorNotification.h"

namespace communication
{
    class HMNotificationVisitor
    {
    public:
        HMNotificationVisitor(){};
        virtual ~HMNotificationVisitor(){};

        virtual void visit(const HMRegisterNotification& command) = 0;
        virtual void visit(const HMHeartbeatNotification& command) = 0;
        virtual void visit(const HMRegisterMainNotification& command) = 0;
        virtual void visit(const HMErrorNotification& command) = 0;
    };
}
#endif
