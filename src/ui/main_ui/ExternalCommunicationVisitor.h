#ifndef AHRS_EXTERNALCOMMUNICATIONVISITOR_H
#define AHRS_EXTERNALCOMMUNICATIONVISITOR_H

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
        UIApplicationManager* uiApplicationManager_;
    };
}

#endif