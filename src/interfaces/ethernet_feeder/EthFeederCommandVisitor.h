#ifndef ETHFEEDERCOMMANDVISITOR_H
#define ETHFEEDERCOMMANDVISITOR_H

#include "EthChangeStateCommand.h"
#include "EthHandshakeCommand.h"
#include "EthInitConnectionCommand.h"

namespace communication
{
    class EthFeederCommandVisitor
    {
    public:
        EthFeederCommandVisitor(){};
        virtual ~EthFeederCommandVisitor(){};

        virtual void visit(EthChangeStateCommand& command) = 0;
        virtual void visit(EthHandshakeCommand& command) = 0;
        virtual void visit(EthInitConnectionCommand& command) = 0;
    };
}

#endif // ETHFEEDERCOMMANDVISITOR_H
