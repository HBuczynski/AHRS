#ifndef AHRS_INTERPROCESSEXTCOMMUNICATIONVISITOR_H
#define AHRS_INTERPROCESSEXTCOMMUNICATIONVISITOR_H

#include "ClientUDPManager.h"

#include <interfaces/communication_process_feeder/FeederCommandVisitor.h>
#include <interfaces/communication_process_feeder/FeederNotificationVisitor.h>
#include <logger/Logger.h>

namespace communication
{
    class InterprocessExtCommunicationVisitor final : virtual public FeederCommandVisitor, virtual public FeederNotificationVisitor
    {
    public:
        InterprocessExtCommunicationVisitor();
        ~InterprocessExtCommunicationVisitor();

        virtual void visit(const CalibrateMgnDemandCommand& command) override ;
        virtual void visit(const communication::FeederWirelessWrapperCommand& command) override;
        virtual void visit(const communication::FeederCodeDemandCommand& command) override;
        virtual void visit(const CalibrationStatusNotification& notification) override;
        virtual void visit(const StateNotification& notification) override;
        virtual void visit(const DbHashNotification& notification) override;
        virtual void visit(const UDPBitsNotification& notification) override;

        void initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager);

    private:
        utility::Logger& logger_;

        std::shared_ptr<ClientUDPManager> clientUDPManager_;
    };
}

#endif
