#ifndef FMVISITOR_H
#define FMVISITOR_H

#include <interfaces/fm/FMCommandVisitor.h>
#include "CommunicationProcessesHandler.h"
#include <logger/Logger.h>
#include "GuiProcessHandler.h"

namespace main_process
{
    class FMVisitor : public communication::FMCommandVisitor
    {
    public:
        FMVisitor();
        ~FMVisitor();

        void initializeCommunicationProcess(CommunicationProcessesHandler *communicationProcessesHandler);
        void initializeGuiProcess(GuiProcessHandler *guiProcessHandler);

        virtual void visit(const communication::FMResetCommunicationProcessCommand& command) override;
        virtual void visit(const communication::FMRestartChangeMasterCommand& command) override;
        virtual void visit(const communication::FMChangeChannelCommand& command) override;

    private:
        CommunicationProcessesHandler *communicationProcessesHandler_;
        GuiProcessHandler *guiProcessHandler_;
        utility::Logger& logger_;
    };
}


#endif // FMVISITOR_H
