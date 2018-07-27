#ifndef AHRS_UICOMMANDVISITOR_H
#define AHRS_UICOMMANDVISITOR_H

#include "UIChangeModeCommand.h"

namespace communication
{
    class UICommandVisitor
    {
    public:
        UICommandVisitor(){};
        virtual ~UICommandVisitor(){};

        virtual void visit(UIChangeModeCommand& command) = 0;

    };
}

#endif //AHRS_UICOMMANDVISITOR_H
