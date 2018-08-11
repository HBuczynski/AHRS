#ifndef AHRS_FEEDERCOMMANDVISITOR_H
#define AHRS_FEEDERCOMMANDVISITOR_H

#include "CalibrateMagnetometerCommand.h"

namespace communication
{
    class FeederCommandVisitor
    {
    public:
        FeederCommandVisitor(){};
        virtual ~FeederCommandVisitor(){};

        virtual void visit(const CalibrateMagnetometerCommand& command);
    };
}

#endif