#include "GUIInterprocessCommandVisitor.h"
#include <QVariant>

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
    windowsContainer_[PagesType::MENU_PAGE] = bind(&GUIInterprocessCommandVisitor::launchMainPage, this);
}

void GUIInterprocessCommandVisitor::initializeSignalsAndSlots()
{
    qRegisterMetaType<uint8_t>("uint8_t");

    QObject::connect(this, SIGNAL(signalWelcomePage()), mainWindow_.get(), SLOT(setWelcomePage()));
    QObject::connect(this, SIGNAL(signalMenuPage()), mainWindow_.get(), SLOT(setMenuPage()));
    QObject::connect(this, SIGNAL(signalEstablishingConnection()), mainWindow_.get(), SLOT(setConnectingPage()));
    QObject::connect(this, SIGNAL(signalSettingPage()), mainWindow_.get(), SLOT(setSettingPage()));
    QObject::connect(this, SIGNAL(signalBITSPage(communication::BitsInformation)), mainWindow_.get(), SLOT(setBITSPage(communication::BitsInformation)));
    QObject::connect(this, SIGNAL(signalPlanesDataset(QString)), mainWindow_.get(), SLOT(setPlanesDataset(QString)));
    QObject::connect(this, SIGNAL(signalCallibrationMode(uint8_t, communication::CalibrationConfiguration)), mainWindow_.get(), SLOT(setCallibrationMode(uint8_t, communication::CalibrationConfiguration)));
    QObject::connect(this, SIGNAL(signalAHRSPage()), mainWindow_.get(), SLOT(setAHRSPage()));
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
            const std::string message = std::string("-GUI- InterprocessCommandVisitor :: Received") + command.getName() + " " + to_string(static_cast<int>(command.getWindowType()));
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const std::string message = std::string("-GUI- InterprocessCommandVisitor :: Received") + command.getName() +  " " + to_string(static_cast<int>(command.getWindowType()))+
                    " with wrong window type.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void GUIInterprocessCommandVisitor::visit(GUIBITSCommand &command)
{
    emit signalBITSPage(command.getBitsInfo());
}

void GUIInterprocessCommandVisitor::visit(communication::GUIPlanesSetCommand& command)
{
    QString planes(command.getDataset().c_str());

    emit signalPlanesDataset(planes);
}

void GUIInterprocessCommandVisitor::visit(communication::GUICallibrationCommand& command)
{
    emit signalCallibrationMode(command.getMode(), command.getCalibrationConfiguration());
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

void GUIInterprocessCommandVisitor::launchMainPage()
{
    emit signalMenuPage();
}

void GUIInterprocessCommandVisitor::launchAHRSWindow()
{
    emit signalAHRSPage();
}

void GUIInterprocessCommandVisitor::launchRestartWindow()
{

}

void GUIInterprocessCommandVisitor::launchShutdownWindow()
{

}
