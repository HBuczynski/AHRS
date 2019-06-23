#ifndef INTERCOMMUNICATIONVISITOR_H
#define INTERCOMMUNICATIONVISITOR_H

#include <interfaces/communication_process_feeder/FeederCommandVisitor.h>

namespace communication
{
    class InterManager;

    class InterCommunicationVisitor : public FeederCommandVisitor
    {
    public:
        InterCommunicationVisitor();
        ~InterCommunicationVisitor();

        virtual void visit(const CalibrateMgnDemandCommand& command) override;
        virtual void visit(const FeederWirelessWrapperCommand& command) override;
        virtual void visit(const FeederCodeDemandCommand& command) override;

        void initializeInterManager(InterManager *manager);

    private:
        InterManager *interManager_;
    };
}

#endif // INTERCOMMUNICATIONVISITOR_H
