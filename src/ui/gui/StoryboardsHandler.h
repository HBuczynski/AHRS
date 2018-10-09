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

#include "MainWindow.h"
#include "PageController.h"
#include "storyboards/ExitPage.h"
#include "storyboards/AHRSPage.h"
#include "storyboards/WelcomePage.h"
#include "storyboards/SystemSetupPage.h"
#include "storyboards/CallibrationSettings.h"
#include "storyboards/RestartPage.h"


class StoryboardsHandler final : public QObject, public gui::PageController
{
    Q_OBJECT
public:
    StoryboardsHandler();

    void setupUi(QMainWindow *MainWindow);

    void backToPreviousPage() override;

    void setWelcomePage() override;
    void setAHRSPage() override;
    void setSystemSetupPage() override;
    void setCallibrationSettingPage() override;
    void setRestartPage() override;
    void setExitPage() override;

public slots:
    void change();

private:

    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QSplitter *splitter;
    QFrame *frame_2;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;

    AHRSPage *ahrsPage;
    ExitPage *exitPage;
    RestartPage *restartPage;
    WelcomePage *welcomePage;
    SystemSetupPage *systemSetupPage_;
    CallibrationSettings *callibrationSettings_;

    QWidget *previousWidget_;
};

#endif
