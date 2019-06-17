#ifndef ETHFEEDERRESPONSEVISITOR_H
#define ETHFEEDERRESPONSEVISITOR_H

#include "EthAckFeederResponse.h"

namespace communication
{
    class EthFeederResponseVisitor
    {
    public:
        EthFeederResponseVisitor() {};
        virtual ~EthFeederResponseVisitor() {};

        virtual void visit(EthAckFeederResponse& command) = 0;
    };
}

#endif // ETHFEEDERRESPONSEVISITOR_H
