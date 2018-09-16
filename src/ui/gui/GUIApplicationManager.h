#ifndef AHRS_GUIAPPLICATIONMANAGER_H
#define AHRS_GUIAPPLICATIONMANAGER_H

#include "MainWindow.h"
#include "StoryboardsHandler.h"
#include "GUIInterprocessCommandVisitor.h"

#include <memory>

namespace gui
{
    class GUIApplicationManager
    {
    public:
        GUIApplicationManager(MainWindow* mainWindow);
        ~GUIApplicationManager();

    private:
        MainWindow* mainWindow_;
        GUIInterprocessCommandVisitor interprocessCommandVisitor_;
    };
}

#endif
