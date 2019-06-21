#ifndef AHRS_FEEDERCOMMANDVISITOR_H
#define AHRS_FEEDERCOMMANDVISITOR_H

#include "CalibrateMgnDemandCommand.h"
#include "FeederWirelessWrapperCommand.h"
#include "FeederCodeDemandCommand.h"

namespace communication
{
    class FeederCommandVisitor
    {
    public:
        FeederCommandVisitor(){};
        virtual ~FeederCommandVisitor(){};

        virtual void visit(const CalibrateMgnDemandCommand& command) = 0;
        virtual void visit(const FeederWirelessWrapperCommand& command) = 0;
        virtual void visit(const FeederCodeDemandCommand& command) = 0;
    };
}

#endif
