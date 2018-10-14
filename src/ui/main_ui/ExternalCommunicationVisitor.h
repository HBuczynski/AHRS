#ifndef AHRS_EXTERNALCOMMUNICATIONVISITOR_H
#define AHRS_EXTERNALCOMMUNICATIONVISITOR_H

#include <utility>
#include <tuple>

#include <interfaces/communication_process_ui/UINotificationVisitor.h>

namespace main_process
{
    class UIApplicationManager;

    class ExternalCommunicationVisitor final : public communication::UINotificationVisitor
    {
    public:
        ExternalCommunicationVisitor(UIApplicationManager *uiApplicationManager);
        ~ExternalCommunicationVisitor();

        virtual void visit(communication::ReceivingDataNotification& command);
        virtual void visit(communication::CommunicationStatusNotification& command);

    private:
        std::tuple<uint8_t , uint8_t , uint8_t > informationParameters_;

        UIApplicationManager* uiApplicationManager_;
    };
}

#endif