#ifndef AHRS_GUIRESPONSEVISITOR_H
#define AHRS_GUIRESPONSEVISITOR_H

#include "GUIPlaneResponse.h"
#include "GUIWindowResponse.h"

namespace communication
{
    class GUIResponseVisitor
    {
    public:
        GUIResponseVisitor() {};
        virtual ~GUIResponseVisitor() {};

        virtual void visit(GUIPlaneResponse& data) = 0;
        virtual void visit(GUIWindowResponse& data) = 0;
    };
}

#endif