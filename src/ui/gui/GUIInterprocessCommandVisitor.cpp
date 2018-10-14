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

GUIInterprocessCommandVisitor::~GUIInterprocessCommandVisitor()
{}

void GUIInterprocessCommandVisitor::initializeWindowsContainer()
{
    windoowsContainer_[WindowType::WELCOME_PAGE] = bind(&GUIInterprocessCommandVisitor::launchStartPage, this);
    windoowsContainer_[WindowType::CONNECTION_ESTABLISHING] = bind(&GUIInterprocessCommandVisitor::launchCommunicationEstablished, this);
    windoowsContainer_[WindowType::CHOOSING_PLANE] = bind(&GUIInterprocessCommandVisitor::launchChoosingPlaneWindow, this);
    windoowsContainer_[WindowType::CALIBRATION] = bind(&GUIInterprocessCommandVisitor::launchCalibrationWindow, this);
    windoowsContainer_[WindowType::AHRS] = bind(&GUIInterprocessCommandVisitor::launchAHRSWindow, this);
    windoowsContainer_[WindowType::RESTART] = bind(&GUIInterprocessCommandVisitor::launchRestartWindow, this);
    windoowsContainer_[WindowType::SHUTDOWN] = bind(&GUIInterprocessCommandVisitor::launchShutdownWindow, this);
}

void GUIInterprocessCommandVisitor::initializeSignalsAndSlots()
{
    qRegisterMetaType<uint8_t>("uint8_t");

    QObject::connect(this, SIGNAL(signalWelcomePage()), mainWindow_.get(), SLOT(setWelcomePage()));
    QObject::connect(this, SIGNAL(signalEstablishingConnection()), mainWindow_.get(), SLOT(setConnectingPage()));
    QObject::connect(this, SIGNAL(signalInformationPage(uint8_t, uint8_t, uint8_t)), mainWindow_.get(), SLOT(setInformationPage(uint8_t, uint8_t, uint8_t)));
}

void GUIInterprocessCommandVisitor::visit(GUIWindowCommand &command)
{
    const auto windowType = command.getWindowType();
    const auto windowsIterator = windoowsContainer_.find(windowType);

    if(windowsIterator != windoowsContainer_.end())
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
    emit signalInformationPage(command.getMasterConnection(), command.getRedundantConnection(), command.getBitsPerformance());
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