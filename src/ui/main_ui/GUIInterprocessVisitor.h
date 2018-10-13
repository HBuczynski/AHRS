#ifndef AHRS_GUICOMMUNICATIONVISITOR_H
#define AHRS_GUICOMMUNICATIONVISITOR_H

#include <interfaces/gui/GUIResponseVisitor.h>

namespace main_process
{
    class UIApplicationManager;

    class GUIInterprocessVisitor final : public communication::GUIResponseVisitor
    {
    public:
        GUIInterprocessVisitor(UIApplicationManager *uiApplicationManager);
        ~GUIInterprocessVisitor();

        void visit(communication::GUIPlaneResponse& data);

    private:
        UIApplicationManager* uiApplicationManager_;
    };
}

#endif