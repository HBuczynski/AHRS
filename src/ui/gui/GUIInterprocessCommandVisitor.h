#ifndef AHRS_GUIINTERPROCESSCOMMANDVISITOR_H
#define AHRS_GUIINTERPROCESSCOMMANDVISITOR_H

#include <map>
#include <memory>
#include <functional>

#include <interfaces/gui/GUICommandVisitor.h>
#include <interfaces/gui/GUIWindowCommand.h>
#include <logger/Logger.h>
#include "MainWindow.h"

namespace gui
{
    class GUIInterprocessCommandVisitor final : public communication::GUICommandVisitor
    {
    public:
        GUIInterprocessCommandVisitor(std::shared_ptr<MainWindow> mainWindow);
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

        std::shared_ptr<MainWindow> mainWindow_;
        utility::Logger& logger_;

    };
}

#endif