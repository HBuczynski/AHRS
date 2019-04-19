#include "GUIInterprocessCommandVisitor.h"

using namespace std;
using namespace gui;
using namespace utility;
using namespace communication;

GUIInterprocessCommandVisitor::GUIInterprocessCommandVisitor(std::shared_ptr<MainWindow> mainWindow)
    :   mainWindow_(mainWindow),
        logger_(Logger::getInstance())
{
    initializeWindowsContainer();
    initializeSignalsAndSlots();
}

void GUIInterprocessCommandVisitor::initializeWindowsContainer()
{
    windowsContainer_[PagesType::WELCOME_PAGE] = bind(&GUIInterprocessCommandVisitor::launchStartPage, this);
    windowsContainer_[PagesType::CONNECTING_PAGE] = bind(&GUIInterprocessCommandVisitor::launchCommunicationEstablished, this);
    windowsContainer_[PagesType::PLANE_SETTING_PAGE] = bind(&GUIInterprocessCommandVisitor::launchChoosingPlaneWindow, this);
    windowsContainer_[PagesType::AHRS_PAGE] = bind(&GUIInterprocessCommandVisitor::launchAHRSWindow, this);
    windowsContainer_[PagesType::RESTART_PAGE] = bind(&GUIInterprocessCommandVisitor::launchRestartWindow, this);
    windowsContainer_[PagesType::EXIT_PAGE] = bind(&GUIInterprocessCommandVisitor::launchShutdownWindow, this);
}

void GUIInterprocessCommandVisitor::initializeSignalsAndSlots()
{
    qRegisterMetaType<uint8_t>("uint8_t");

    QObject::connect(this, SIGNAL(signalWelcomePage()), mainWindow_.get(), SLOT(setWelcomePage()));
    QObject::connect(this, SIGNAL(signalEstablishingConnection()), mainWindow_.get(), SLOT(setConnectingPage()));
    QObject::connect(this, SIGNAL(signalSettingPage()), mainWindow_.get(), SLOT(setSettingPage()));
    QObject::connect(this, SIGNAL(signalInformationPage(uint8_t, uint8_t, uint8_t, uint8_t)), mainWindow_.get(), SLOT(setInformationPage(uint8_t, uint8_t, uint8_t, uint8_t)));
}

void GUIInterprocessCommandVisitor::visit(GUIWindowCommand &command)
{
    const auto windowType = command.getWindowType();
    const auto windowsIterator = windowsContainer_.find(windowType);

    if(windowsIterator != windowsContainer_.end())
    {
        windowsIterator->second();

        if(logger_.isInformationEnable())
        {
            const std::string message = std::string("GUIInterprocessCommandVisitor :: Received") + command.getName();
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const std::string message = std::string("GUIInterprocessCommandVisitor :: Received") + command.getName() + " with wrong window type.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void GUIInterprocessCommandVisitor::visit(GUIInformationWindowCommand &command)
{
    emit signalInformationPage(command.getMasterConnection(), command.getRedundantConnection(), command.getBitsMaster(), command.getBitsRedundant());
}

void GUIInterprocessCommandVisitor::launchStartPage()
{
    emit signalWelcomePage();
}

void GUIInterprocessCommandVisitor::launchCommunicationEstablished()
{
    emit signalEstablishingConnection();
}

void GUIInterprocessCommandVisitor::launchActiveConnectionWindow()
{

}

void GUIInterprocessCommandVisitor::launchChoosingPlaneWindow()
{
    emit signalSettingPage();
}

void GUIInterprocessCommandVisitor::launchCalibrationWindow()
{

}

void GUIInterprocessCommandVisitor::launchAHRSWindow()
{

}

void GUIInterprocessCommandVisitor::launchRestartWindow()
{

}

void GUIInterprocessCommandVisitor::launchShutdownWindow()
{

}
