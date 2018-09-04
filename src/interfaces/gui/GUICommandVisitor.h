#ifndef AHRS_GGUICommandVISITOR_H
#define AHRS_GGUICommandVISITOR_H

#include "GUIWindowCommand.h"

namespace communication
{
    class GUICommandVisitor
    {
    public:
        GUICommandVisitor(){};
        virtual ~GUICommandVisitor(){};

        virtual void visit(GUIWindowCommand& command) = 0;
    };
}

#endif