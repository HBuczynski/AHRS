#include <iostream>
#include <math.h>
#include <thread>

#include "MainWindow.h"
#include "StoryboardsHandler.h"

using namespace std;

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    storyboardsHandler_( new StoryboardsHandler )
{
    qRegisterMetaType<communication::CalibrationConfiguration>();
    qRegisterMetaType<communication::BitsInformation>();
    storyboardsHandler_->setupUi( this );
}

MainWindow::~MainWindow()
{
    delete storyboardsHandler_;
}

void MainWindow::setWelcomePage()
{
    storyboardsHandler_->setWelcomePage();
}

void MainWindow::setAHRSPage()
{
    storyboardsHandler_->setAHRSPage();
}

void MainWindow::setSystemSetupPage()
{
    storyboardsHandler_->setSystemSetupPage();
}

void MainWindow::setSettingPage()
{
    storyboardsHandler_->setPlaneSettingPage();
}

void MainWindow::setRestartPage()
{
    storyboardsHandler_->setRestartPage();
}

void MainWindow::setExitPage()
{
    storyboardsHandler_->setExitPage();
}

void MainWindow::setLogsPage()
{
    storyboardsHandler_->setLogsPage();
}

void MainWindow::setMenuPage()
{
    storyboardsHandler_->setMenuPage();
}

void MainWindow::setConnectingPage()
{
    storyboardsHandler_->setConnectingPage();
}

void MainWindow::setBITSPage(communication::BitsInformation info)
{
    storyboardsHandler_->setBitsInformation(info);
}

void MainWindow::setPlanesDataset(QString planes)
{
    storyboardsHandler_->setPlaneDataset(planes.toStdString());
}

void MainWindow::setCallibrationMode(uint8_t mode, communication::CalibrationConfiguration parameters)
{
    if(mode)
    {
        storyboardsHandler_->setMainCallibrationParameters(parameters);
    }
    else
    {
        storyboardsHandler_->setRedundantCallibrationParameters(parameters);
    }
}
