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

void MainWindow::setWidgetPFDPage()
{
    storyboardsHandler_->setWidgetPFDPage();
}

void MainWindow::setSystemSetupPage()
{
    storyboardsHandler_->setSystemSetupPage();
}

