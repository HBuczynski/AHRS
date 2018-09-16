#include "GUIApplicationManager.h"
#include "MainWindow.h"

using namespace gui;
using namespace std;

GUIApplicationManager::GUIApplicationManager(MainWindow *mainWindow)
    : mainWindow_(mainWindow)
{
    mainWindow_->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    mainWindow_->show();

    mainWindow_->setWelcomePage();
}

GUIApplicationManager::~GUIApplicationManager()
{}
