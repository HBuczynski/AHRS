#ifndef AHRS_GUIINTERPROCESSCOMMANDVISITOR_H
#define AHRS_GUIINTERPROCESSCOMMANDVISITOR_H

#include <QString>
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
        void visit(communication::GUIPlanesSetCommand& command) override;
        void visit(communication::GUICallibrationCommand& command) override;

    signals:
        void signalWelcomePage();
        void signalEstablishingConnection();
        void signalSettingPage();
        void signalMenuPage();
        void signalInformationPage(uint8_t, uint8_t, uint8_t, uint8_t);
        void signalPlanesDataset(QString);
        void signalCallibrationMode(uint8_t, communication::CallibrationConfiguration);

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
        void launchMainPage();

        std::map<PagesType, std::function<void()>> windowsContainer_;

        std::shared_ptr<MainWindow> mainWindow_;
        utility::Logger& logger_;
    };
}

#endif
