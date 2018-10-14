#include "StoryboardsHandler.h"

#include <iostream>

using namespace std;

StoryboardsHandler::StoryboardsHandler()
    : previousWidget_(nullptr)
{}

void StoryboardsHandler::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
    {
        MainWindow->setObjectName(QStringLiteral("MainWindow"));
    }

    QPalette pal = MainWindow->palette();
    pal.setColor(QPalette::Window, Qt::black);

    MainWindow->resize(1024, 600);
    MainWindow->setMaximumSize(QSize(1024, 600));
    MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    MainWindow->setPalette(pal);

    centralWidget = make_unique<QWidget>(MainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    centralWidget->setMaximumSize(QSize(1024, 600));

    gridLayout_5 = make_unique<QGridLayout>(centralWidget.get());
    gridLayout_5->setSpacing(2);
    gridLayout_5->setContentsMargins(2, 2, 2, 2);
    gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));

    splitter = make_unique<QSplitter>(centralWidget.get());
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setEnabled(true);
    splitter->setMaximumSize(QSize(1024, 600));
    splitter->setOrientation(Qt::Horizontal);
    frame_2 = make_unique<QFrame>(splitter.get());
    frame_2->setObjectName(QStringLiteral("frame_2"));
    frame_2->setMaximumSize(QSize(1024, 600));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);

    gridLayout_4 = make_unique<QGridLayout>(frame_2.get());
    gridLayout_4->setSpacing(2);
    gridLayout_4->setContentsMargins(2, 2, 2, 2);
    gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
    gridLayout_4->setSizeConstraint(QLayout::SetMaximumSize);
    gridLayout_4->setContentsMargins(0, 3, 0, 3);
    gridLayout_2 = make_unique<QGridLayout>();
    gridLayout_2->setSpacing(2);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayout_2->setSizeConstraint(QLayout::SetMaximumSize);

    gridLayout_4->addLayout(gridLayout_2.get(), 0, 0, 1, 1);
    splitter->addWidget(frame_2.get());
    gridLayout_5->addWidget(splitter.get(), 0, 0, 1, 1);

    MainWindow->setCentralWidget(centralWidget.get());
    QMetaObject::connectSlotsByName(MainWindow);
}

void StoryboardsHandler::backToPreviousPage()
{

}

void StoryboardsHandler::setWelcomePage()
{
    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    welcomePage_ = new WelcomePage();
    welcomePage_->resize(QSize(1024, 600));

    gridLayout_2->addWidget(welcomePage_);
    previousWidget_ = welcomePage_;
}

void StoryboardsHandler::setAHRSPage()
{
    ahrsPage_ = new AHRSPage(this);
    ahrsPage_->resize(QSize(1024, 600));
    ahrsPage_->initialize();

    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    gridLayout_2->addWidget(ahrsPage_);
    previousWidget_ = ahrsPage_;
}

void StoryboardsHandler::setSystemSetupPage()
{
    systemSetupPage_ = new SystemSetupPage();
    systemSetupPage_->resize(QSize(1024, 600));

    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    gridLayout_2->addWidget(systemSetupPage_);
    previousWidget_ = systemSetupPage_;

}

void StoryboardsHandler::setCallibrationSettingPage()
{
    calibrationSettings_ = new CallibrationSettings();
    calibrationSettings_->resize(QSize(1024, 600));

    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    gridLayout_2->addWidget(calibrationSettings_);
    previousWidget_ = calibrationSettings_;
}

void StoryboardsHandler::setRestartPage()
{
    restartPage_ = new RestartPage();
    restartPage_->resize(QSize(1024, 600));

    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    gridLayout_2->addWidget(restartPage_);
    previousWidget_ = restartPage_;
}

void StoryboardsHandler::setExitPage()
{
    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    exitPage_ = new ExitPage(this);
    exitPage_->resize(QSize(1024, 600));
    exitPage_->initialize();

    gridLayout_2->addWidget(exitPage_);
    previousWidget_ = exitPage_;
}

void StoryboardsHandler::setLogsPage()
{
    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    logsPage_ = new LogsPage(this);
    logsPage_->resize(QSize(1024, 600));
    logsPage_->initialize();

    gridLayout_2->addWidget(logsPage_);
    previousWidget_ = logsPage_;
}

void StoryboardsHandler::setMenuPage()
{
    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    mainPage_ = new MainPage(this);
    mainPage_->resize(QSize(1024, 600));
    mainPage_->initialize();

    gridLayout_2->addWidget(mainPage_);
    previousWidget_ = mainPage_;
}

void StoryboardsHandler::setConnectingPage()
{
    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    connectingPage_ = new ConnectingPage();
    connectingPage_->resize(QSize(1024, 600));

    gridLayout_2->addWidget(connectingPage_);
    previousWidget_ = connectingPage_;
}

void StoryboardsHandler::setInformationPage(uint8_t master, uint8_t redundant, uint8_t bits)
{
    if(previousWidget_)
    {
        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    informationPage_ = new InformationPage(this);
    informationPage_->resize(QSize(1024, 600));

    if(master == 1 && redundant == 1 && bits == 1)
    {
        informationPage_->initializeContinue();
    }
    else
    {
        informationPage_->initializeExit();
    }

    if(master == 1)
    {
        informationPage_->setMasterConnectionEstablished();
    }
    else if (master == 0)
    {
        informationPage_->setMasterConnectionFailed();
    }

    if(redundant == 1)
    {
        informationPage_->setSecondaryConnectionEstablished();
    }
    else if (redundant == 0)
    {
        informationPage_->setSecondaryConnectionFailed();
    }

    if(bits == 1)
    {
        informationPage_->setBITS();
    }
    else if (bits == 0)
    {
        informationPage_->setBITSFailed();
    }

    gridLayout_2->addWidget(informationPage_);
    previousWidget_ = informationPage_;
}