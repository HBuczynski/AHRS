#ifndef AHRS_FEEDERCOMMANDVISITOR_H
#define AHRS_FEEDERCOMMANDVISITOR_H

#include "CalibrateMgnDemandCommand.h"

namespace communication
{
    class FeederCommandVisitor
    {
    public:
        FeederCommandVisitor(){};
        virtual ~FeederCommandVisitor(){};

        virtual void visit(const CalibrateMgnDemandCommand& command);
    };
}

#endif