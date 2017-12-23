#ifndef AHRS_BLACK_BOX_FRAMEVISITOR_H
#define AHRS_BLACK_BOX_FRAMEVISITOR_H

#include "InitConnectionCommand.h"
#include "EndConnectionCommand.h"

namespace communication
{
    class CommandVisitor
    {
    public:
        CommandVisitor();
        virtual ~CommandVisitor();

        virtual void visit(InitConnectionCommand& command) = 0;
        virtual void visit(EndConnectionCommand& command) = 0;
    };
}
#endif
