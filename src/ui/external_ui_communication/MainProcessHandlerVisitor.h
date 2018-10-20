#ifndef AHRS_MAINPROCESSHANDLERVISITOR_H
#define AHRS_MAINPROCESSHANDLERVISITOR_H

#include <memory>
#include "CommunicationManagerUI.h"

#include <interfaces/communication_process_ui/UICommandVisitor.h>
#include <interfaces/wireless_commands/CommandFactory.h>

#include <logger/Logger.h>

namespace communication
{
    class MainProcessHandlerVisitor final : public UICommandVisitor
    {
    public:
        MainProcessHandlerVisitor(std::shared_ptr<CommunicationManagerUI> communicationManager);
        ~MainProcessHandlerVisitor();

        virtual void visit(UIChangeModeCommand& command) override;
        virtual void visit(ShutdownCommand& command) override;
        virtual void visit(ReconnectCommand& command) override;
        virtual void visit(SendingDataCommand& command) override;

    private:
        std::shared_ptr<CommunicationManagerUI> communicationManager_;
        CommandFactory wirelessCommandFactory_;

        utility::Logger& logger_;
    };
}

#endif
