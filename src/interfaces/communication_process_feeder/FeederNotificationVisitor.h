#ifndef AHRS_FEEDERNOTIFICATIONVISITOR_H
#define AHRS_FEEDERNOTIFICATIONVISITOR_H

#include "CalibrationStatusNotification.h"
#include "StateNotification.h"
#include "DbHashNotification.h"

namespace communication
{
    class FeederNotificationVisitor
    {
    public:
        FeederNotificationVisitor(){};
        virtual ~FeederNotificationVisitor(){};

        virtual void visit(const CalibrationStatusNotification& command) = 0;
        virtual void visit(const StateNotification& command) = 0;
        virtual void visit(const DbHashNotification& command) = 0;
    };
}
#endif
