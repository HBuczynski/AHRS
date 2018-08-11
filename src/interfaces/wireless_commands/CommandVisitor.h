#ifndef AHRS_BLACK_BOX_FRAMEVISITOR_H
#define AHRS_BLACK_BOX_FRAMEVISITOR_H

#include "InitConnectionCommand.h"
#include "EndConnectionCommand.h"
#include "CallibrateMagnetometerCommand.h"
#include "CollectDataCommand.h"
#include "SetPlaneMagnetometerCommand.h"
#include "RemovePlaneDataCommand.h"

namespace communication
{
    class CommandVisitor
    {
    public:
        CommandVisitor(){};
        virtual ~CommandVisitor(){};

        virtual void visit(InitConnectionCommand& command) = 0;
        virtual void visit(EndConnectionCommand& command) = 0;
        virtual void visit(CallibrateMagnetometerCommand& command) = 0;
        virtual void visit(CollectDataCommand& command) = 0;
        virtual void visit(SetPlaneMagnetometerCommand& command) = 0;
        virtual void visit(RemovePlaneDataCommand& command) = 0;
    };
}
#endif
