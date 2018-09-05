#ifndef AHRS_GUIINTERPROCESSCOMMANDVISITOR_H
#define AHRS_GUIINTERPROCESSCOMMANDVISITOR_H

#include <map>
#include <functional>

#include <interfaces/gui/GUICommandVisitor.h>
#include <interfaces/gui/GUIWindowCommand.h>
#include <logger/Logger.h>

namespace gui
{
    class GUIInterprocessCommandVisitor : public communication::GUICommandVisitor
    {
    public:
        GUIInterprocessCommandVisitor();
        ~GUIInterprocessCommandVisitor();

        void visit(communication::GUIWindowCommand& command) override;

    private:

        void initializeWindowsContainer();

        void launchStartUPWindow();
        void launchActiveConnectionWindow();
        void launchChoosingPlaneWindow();
        void launchCalibrationWindow();
        void launchAHRSWindow();
        void launchRestartWindow();
        void launchShutdownWindow();


        std::map<communication::WindowType, std::function<void()>> windoowsContainer_;

        utility::Logger& logger_;

    };
}

#endif