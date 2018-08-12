#ifndef AHRS_FEEDERNOTIFICATIONVISITOR_H
#define AHRS_FEEDERNOTIFICATIONVISITOR_H

#include "CalibrationStatusNotification.h"

namespace communication
{
    class FeederNotificationVisitor
    {
    public:
        FeederNotificationVisitor(){};
        virtual ~FeederNotificationVisitor(){};

        virtual void visit(const CalibrationStatusNotification& command) = 0;
    };
}
#endif