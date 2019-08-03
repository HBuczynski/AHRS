#ifndef AHRS_EXTERNALCOMMUNICATIONVISITOR_H
#define AHRS_EXTERNALCOMMUNICATIONVISITOR_H

#include <utility>
#include <tuple>

#include <interfaces/communication_process_ui/UINotificationVisitor.h>
#include <common/FeederStates.h>
#include <logger/Logger.h>

namespace main_process
{
    class UIApplicationManager;

    class ExternalCommInterprocessVisitor final : public communication::UINotificationVisitor
    {
    public:
        ExternalCommInterprocessVisitor(UIApplicationManager *uiApplicationManager);
        ~ExternalCommInterprocessVisitor();

        virtual void visit(communication::ReceivingDataNotification& command);
        virtual void visit(communication::CommunicationStatusNotification& command);
        virtual void visit(communication::DatabaseNameNotification& command);

    private:
        void handleFeederState(FeederStateCode feederCode);

        void initConnection(config::UICommunicationMode mode);

        std::tuple<uint8_t , uint8_t , uint8_t, uint8_t> informationParameters_;

        bool correctInitialization_;
        UIApplicationManager* uiApplicationManager_;
        utility::Logger& logger_;
    };
}

#endif
