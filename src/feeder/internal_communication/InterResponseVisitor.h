#ifndef INTERRESPONSEVISITOR_H
#define INTERRESPONSEVISITOR_H

#include <interfaces/ethernet_feeder/EthFeederResponseVisitor.h>
#include <logger/Logger.h>

namespace communication
{
    class InterResponseVisitor : public EthFeederResponseVisitor
    {
    public:
        InterResponseVisitor();
        ~InterResponseVisitor();

        virtual void visit(EthAckFeederResponse& command) override;

    private:
        utility::Logger& logger_;
    };
}

#endif // INTERRESPONSEVISITOR_H
