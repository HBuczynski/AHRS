#ifndef HMCOMMANDVISITOR_H
#define HMCOMMANDVISITOR_H

#include "HMErrorCommand.h"

namespace communication
{
    class HMCommandVisitor
    {
    public:
        HMCommandVisitor(){};
        virtual ~HMCommandVisitor(){};

        virtual void visit(const HMErrorCommand& command) = 0;
    };
}

#endif // HMCOMMANDVISITOR_H
