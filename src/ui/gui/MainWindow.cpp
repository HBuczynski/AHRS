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

void MainWindow::setCallibrationSettingPage()
{
    storyboardsHandler_->setCallibrationSettingPage();
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

void MainWindow::setInformationPage()
{
    storyboardsHandler_->setInformationPageConnectionOK();
}

void MainWindow::setInformationPageBITOk()
{
    storyboardsHandler_->setInformationPageBitOK();
}

void MainWindow::setInformationPageBITFalse()
{
    storyboardsHandler_->setInformationPageBitFalse();
}