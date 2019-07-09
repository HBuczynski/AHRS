#ifndef FMCOMMANDVISITOR_H
#define FMCOMMANDVISITOR_H

#include "FMResetCommunicationProcessCommand.h"

namespace communication
{
    class FMCommandVisitor
    {
    public:
        FMCommandVisitor(){};
        virtual ~FMCommandVisitor(){};

        virtual void visit(const FMResetCommunicationProcessCommand& command) = 0;
    };
}


#endif // FMCOMMANDVISITOR_H
