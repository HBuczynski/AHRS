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

    storyboardsHandler_->setWelcomePage();

    storyboardsHandler_->setWidgetPFDPage();

//    storyboardsHandler_->setSystemSetupPage();
}

MainWindow::~MainWindow()
{
    delete storyboardsHandler_;
}


