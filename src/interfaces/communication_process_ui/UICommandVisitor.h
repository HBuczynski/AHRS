#ifndef AHRS_UICOMMANDVISITOR_H
#define AHRS_UICOMMANDVISITOR_H

#include "UIChangeModeCommand.h"
#include "ShutdownCommand.h"
#include "ReconnectCommand.h"
#include "SendingDataCommand.h"
#include "DatabaseHashCommand.h"

namespace communication
{
    class UICommandVisitor
    {
    public:
        UICommandVisitor(){};
        virtual ~UICommandVisitor(){};

        virtual void visit(UIChangeModeCommand& command) = 0;
        virtual void visit(ShutdownCommand& command) = 0;
        virtual void visit(ReconnectCommand& command) = 0;
        virtual void visit(SendingDataCommand& command) = 0;
        virtual void visit(DatabaseHashCommand& command) = 0;
    };
}

#endif
