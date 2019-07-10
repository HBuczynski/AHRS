#ifndef FMCOMMANDVISITOR_H
#define FMCOMMANDVISITOR_H

#include "FMResetCommunicationProcessCommand.h"
#include "FMRestartChangeMasterCommand.h"

namespace communication
{
    class FMCommandVisitor
    {
    public:
        FMCommandVisitor(){};
        virtual ~FMCommandVisitor(){};

        virtual void visit(const FMResetCommunicationProcessCommand& command) = 0;
        virtual void visit(const FMRestartChangeMasterCommand& command) = 0;
    };
}


#endif // FMCOMMANDVISITOR_H
