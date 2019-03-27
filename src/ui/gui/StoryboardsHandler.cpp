#include "StoryboardsHandler.h"

#include <iostream>
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace gui;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

StoryboardsHandler::StoryboardsHandler()
    : previousWidget_(nullptr),
      uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
      previousPage_(PagesType::WELCOME_PAGE),
      currentPage_(PagesType::WELCOME_PAGE),
      informationParameters_(42,42,42,42),
      logger_(Logger::getInstance())
{
    inititalizeMessageQueue();

    initializeStoryboardsContainer();
}

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

void StoryboardsHandler::initializeStoryboardsContainer()
{
    storyboardsContainer_[PagesType::WELCOME_PAGE] =  bind(&StoryboardsHandler::setWelcomePage, this);
    storyboardsContainer_[PagesType::AHRS_PAGE] =  bind(&StoryboardsHandler::setAHRSPage, this);
    storyboardsContainer_[PagesType::CALLIBRATION_SETTING_PAGE] =  bind(&StoryboardsHandler::setCallibrationSettingPage, this);
    storyboardsContainer_[PagesType::CONNECTING_PAGE] =  bind(&StoryboardsHandler::setConnectingPage, this);
    storyboardsContainer_[PagesType::EXIT_PAGE] =  bind(&StoryboardsHandler::setExitPage, this);
    storyboardsContainer_[PagesType::LOGS_PAGE] =  bind(&StoryboardsHandler::setLogsPage, this);
    storyboardsContainer_[PagesType::MENU_PAGE] =  bind(&StoryboardsHandler::setMenuPage, this);
    storyboardsContainer_[PagesType::RESTART_PAGE] =  bind(&StoryboardsHandler::setRestartPage, this);
    storyboardsContainer_[PagesType::SYSTEM_SETUP_PAGE] =  bind(&StoryboardsHandler::setSystemSetupPage, this);
}

void StoryboardsHandler::backToPreviousPage()
{
    if(previousPage_ == PagesType::INFORMATION_PAGE)
    {
        setInformationPage(get<0>(informationParameters_), get<1>(informationParameters_), get<2>(informationParameters_), get<3>(informationParameters_));
    }
    else
    {
        const auto iter = storyboardsContainer_.find(previousPage_);
        if( iter != storyboardsContainer_.end())
        {
            iter->second();
        }
    }
}

void StoryboardsHandler::setWelcomePage()
{
    welcomePage_ = new WelcomePage();
    welcomePage_->resize(QSize(1024, 600));

    if(previousWidget_)
    {
        previousPage_ = currentPage_;
        currentPage_ = PagesType::WELCOME_PAGE;

        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

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
        previousPage_ = currentPage_;
        currentPage_ = PagesType::AHRS_PAGE;

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
        previousPage_ = currentPage_;
        currentPage_ = PagesType::SYSTEM_SETUP_PAGE;

        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    gridLayout_2->addWidget(systemSetupPage_);
    previousWidget_ = systemSetupPage_;

}

void StoryboardsHandler::setCallibrationSettingPage()
{
    calibrationSettings_ = new CallibrationSettings(this);
    calibrationSettings_->resize(QSize(1024, 600));
    calibrationSettings_->initialize();

    if(previousWidget_)
    {
        previousPage_ = currentPage_;
        currentPage_ = PagesType::CALLIBRATION_SETTING_PAGE;

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
        previousPage_ = currentPage_;
        currentPage_ = PagesType::RESTART_PAGE;

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
        previousPage_ = currentPage_;
        currentPage_ = PagesType::EXIT_PAGE;

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
        previousPage_ = currentPage_;
        currentPage_ = PagesType::LOGS_PAGE;

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
        previousPage_ = currentPage_;
        currentPage_ = PagesType::MENU_PAGE;

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
        previousPage_ = currentPage_;
        currentPage_ = PagesType::CONNECTING_PAGE;

        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    connectingPage_ = new ConnectingPage();
    connectingPage_->resize(QSize(1024, 600));

    gridLayout_2->addWidget(connectingPage_);
    previousWidget_ = connectingPage_;
}

void StoryboardsHandler::setInformationPage(uint8_t master, uint8_t redundant, uint8_t masterBITs, uint8_t redundantBITs)
{
    if(previousWidget_)
    {
        previousPage_ = currentPage_;
        currentPage_ = PagesType::INFORMATION_PAGE;

        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    informationPage_ = new InformationPage(this);
    informationPage_->resize(QSize(1024, 600));

    if(master == 1 && masterBITs == 1 )//&& redundant ==1 && redundantBITs ==1)
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

    if(masterBITs == 1)
    {
        informationPage_->setBITSMaster();
    }
    else if (masterBITs == 0)
    {
        informationPage_->setBITSMasterFailed();
    }

    if(redundantBITs == 1)
    {
        informationPage_->setBITSRedundant();
    }
    else if (redundantBITs == 0)
    {
        informationPage_->setBITRedundantFailed();
    }

    informationParameters_= make_tuple(master, redundant, masterBITs, redundantBITs);

    gridLayout_2->addWidget(informationPage_);
    previousWidget_ = informationPage_;
}

void StoryboardsHandler::sendToMainProcess(std::vector<uint8_t> msg)
{
    sendingMessageQueue_->send(msg);

    if (logger_.isInformationEnable())
    {
        const std::string message = string("StoryboardsHandler:: Send msg to main process.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void StoryboardsHandler::inititalizeMessageQueue()
{
    try
    {
        sendingMessageQueue_ = make_unique<MessageQueueWrapper>(uiMessageQueuesParameters_.mainProcessQueueName, uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("StoryboardsHandler:: During openning main queue - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("StoryboardsHandler:: Main massage queue initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
