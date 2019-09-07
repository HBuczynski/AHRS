#ifndef AHRS_GUIRESPONSEVISITOR_H
#define AHRS_GUIRESPONSEVISITOR_H

#include "GUIPlaneResponse.h"
#include "GUIWindowResponse.h"
#include "GUIWirelessComWrapperResponse.h"
#include "GUIStartAcqResponse.h"
#include "GUIStopAcqResponse.h"
#include "GUIRestartResponse.h"
#include "GUIShutdownResponse.h"

namespace communication
{
    class GUIResponseVisitor
    {
    public:
        GUIResponseVisitor() {};
        virtual ~GUIResponseVisitor() {};

        virtual void visit(GUIPlaneResponse& data) = 0;
        virtual void visit(GUIWindowResponse& data) = 0;
        virtual void visit(GUIWirelessComWrapperResponse& data) = 0;
        virtual void visit(GUIStartAcqResponse& data) = 0;
        virtual void visit(GUIStopAcqResponse& data) = 0;
        virtual void visit(GUIRestartResponse& data) = 0;
        virtual void visit(GUIShutdownResponse& data) = 0;
    };
}

#endif
