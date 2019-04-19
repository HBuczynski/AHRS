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
    class GUIInterprocessCommandVisitor: public QWidget, public communication::GUICommandVisitor
    {
        Q_OBJECT
    public:
        GUIInterprocessCommandVisitor(std::shared_ptr<MainWindow> mainWindow);

        void visit(communication::GUIWindowCommand& command) override;
        void visit(communication::GUIInformationWindowCommand& command) override;

    signals:
        void signalWelcomePage();
        void signalEstablishingConnection();
        void signalSettingPage();
        void signalInformationPage(uint8_t, uint8_t, uint8_t, uint8_t);

    private:
        void initializeWindowsContainer();
        void initializeSignalsAndSlots();

        void launchStartPage();
        void launchCommunicationEstablished();
        void launchActiveConnectionWindow();
        void launchChoosingPlaneWindow();
        void launchCalibrationWindow();
        void launchAHRSWindow();
        void launchRestartWindow();
        void launchShutdownWindow();

        std::map<PagesType, std::function<void()>> windowsContainer_;

        std::shared_ptr<MainWindow> mainWindow_;
        utility::Logger& logger_;
    };
}

#endif
