#ifndef HMCOMMANDVISITOR_H
#define HMCOMMANDVISITOR_H

#include "HMErrorCommand.h"
#include "HMInvalidConnectionCommand.h"

namespace communication
{
    class HMCommandVisitor
    {
    public:
        HMCommandVisitor(){};
        virtual ~HMCommandVisitor(){};

        virtual void visit(const HMErrorCommand& command) = 0;
        virtual void visit(const HMInvalidConnectionCommand& command) = 0;
    };
}

#endif // HMCOMMANDVISITOR_H
