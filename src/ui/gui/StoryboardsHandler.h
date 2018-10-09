#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

#include <memory>

#include "MainWindow.h"
#include "PageController.h"
#include "storyboards/ExitPage.h"
#include "storyboards/AHRSPage.h"
#include "storyboards/WelcomePage.h"
#include "storyboards/SystemSetupPage.h"
#include "storyboards/CallibrationSettings.h"
#include "storyboards/RestartPage.h"


class StoryboardsHandler final : public gui::PageController
{
    Q_OBJECT
public:
    StoryboardsHandler();

    void setupUi(QMainWindow *MainWindow);

public slots:
    void backToPreviousPage() override;
    void setWelcomePage() override;
    void setSystemSetupPage() override;
    void setCallibrationSettingPage() override;
    void setRestartPage() override;
    void setExitPage() override;
    void setAHRSPage() override;

private:

    std::unique_ptr<QWidget> centralWidget;
    std::unique_ptr<QGridLayout> gridLayout_5;
    std::unique_ptr<QSplitter> splitter;
    std::unique_ptr<QFrame> frame_2;
    std::unique_ptr<QGridLayout> gridLayout_4;
    std::unique_ptr<QGridLayout> gridLayout_2;

    AHRSPage* ahrsPage_;
    ExitPage* exitPage_;
    RestartPage* restartPage_;
    WelcomePage* welcomePage_;
    SystemSetupPage* systemSetupPage_;
    CallibrationSettings* callibrationSettings_;

    QWidget *previousWidget_;
};

#endif
