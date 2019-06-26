#include "StoryboardsHandler.h"

#include <iostream>
#include <config_reader/ConfigurationReader.h>

#include <interfaces/wireless_commands/StartAcquisitionCommand.h>
#include <interfaces/gui/GUIWirelessComWrapperResponse.h>
#include <interfaces/gui/GUIStartAcqResponse.h>

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
    storyboardsContainer_[PagesType::PLANE_SETTING_PAGE] =  bind(&StoryboardsHandler::setPlaneSettingPage, this);
    storyboardsContainer_[PagesType::CONNECTING_PAGE] =  bind(&StoryboardsHandler::setConnectingPage, this);
    storyboardsContainer_[PagesType::EXIT_PAGE] =  bind(&StoryboardsHandler::setExitPage, this);
    storyboardsContainer_[PagesType::GPS_PAGE] =  bind(&StoryboardsHandler::setGpsPage, this);
    storyboardsContainer_[PagesType::MENU_PAGE] =  bind(&StoryboardsHandler::setMenuPage, this);
    storyboardsContainer_[PagesType::RESTART_PAGE] =  bind(&StoryboardsHandler::setRestartPage, this);
    storyboardsContainer_[PagesType::SYSTEM_SETUP_PAGE] =  bind(&StoryboardsHandler::setSystemSetupPage, this);
}

void StoryboardsHandler::backToPreviousPage()
{
    if(previousPage_ == PagesType::CONNECTING_PAGE)
    {
        //DO NOTHING
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

    GUIStartAcqResponse startAcq;
    sendToMainProcess(startAcq.getFrameBytes());

    StartAcquisitionCommand command;
    GUIWirelessComWrapperResponse response(UICommunicationMode::MASTER, command.getFrameBytes());
    sendToMainProcess(response.getFrameBytes());

    setSystemActivation();
    setBITSActive();
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

void StoryboardsHandler::setPlaneSettingPage()
{
    planeSettings_ = new PlaneSettingsPage(this, guiDataManager_.getPlaneDataset());
    planeSettings_->resize(QSize(1024, 600));
    planeSettings_->initialize();

    if(previousWidget_)
    {
        previousPage_ = currentPage_;
        currentPage_ = PagesType::PLANE_SETTING_PAGE;

        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    gridLayout_2->addWidget(planeSettings_);
    previousWidget_ = planeSettings_;
}

void StoryboardsHandler::setCallibrationPage()
{
    callibrationPage_ = new CallibrationPage(this);
    callibrationPage_->resize(QSize(1024, 600));
    callibrationPage_->initialize();

    if(previousWidget_)
    {
        previousPage_ = currentPage_;
        currentPage_ = PagesType::CALLIBRATION_PAGE;

        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    gridLayout_2->addWidget(callibrationPage_);
    previousWidget_ = callibrationPage_;
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

void StoryboardsHandler::setGpsPage()
{
    if(previousWidget_)
    {
        previousPage_ = currentPage_;
        currentPage_ = PagesType::GPS_PAGE;

        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    gpsPage_ = new GpsPage(this);
    gpsPage_->resize(QSize(1024, 600));
    gpsPage_->initialize();

    gridLayout_2->addWidget(gpsPage_);
    previousWidget_ = gpsPage_;

    GUIStartAcqResponse startAcq;
    sendToMainProcess(startAcq.getFrameBytes());

    StartAcquisitionCommand command;
    GUIWirelessComWrapperResponse response(UICommunicationMode::MASTER, command.getFrameBytes());
    sendToMainProcess(response.getFrameBytes());
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

void StoryboardsHandler::setBITSPage()
{
    if(previousWidget_)
    {
        previousPage_ = currentPage_;
        currentPage_ = PagesType::BITS_PAGE;

        gridLayout_2->removeWidget(previousWidget_);
        delete previousWidget_;
    }

    bitsPage_ = new InformationPage(this);
    bitsPage_->resize(QSize(1024, 600));
    bitsPage_->initialize();


    gridLayout_2->addWidget(bitsPage_);
    previousWidget_ = bitsPage_;
}

void StoryboardsHandler::sendToMainProcess(vector<uint8_t> msg)
{
    sendingMessageQueue_->send(msg);

    if (logger_.isInformationEnable())
    {
        const string message = string("-GUI- StoryboardsHandler:: Send msg to main process.");
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
            const string message = string("-GUI- StoryboardsHandler:: During openning main queue - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const string message = string("-GUI- StoryboardsHandler:: Main massage queue initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void StoryboardsHandler::setPlaneName(const string& name)
{
    guiDataManager_.setPlaneName(name);
}

const string& StoryboardsHandler::getPlaneName()
{
    return guiDataManager_.getPlaneName();
}

void StoryboardsHandler::setPlaneDataset(const string& name)
{
    guiDataManager_.setPlaneDataset(name);

    if(currentPage_ == PagesType::PLANE_SETTING_PAGE)
    {
        const auto temp = previousPage_;
        setPlaneSettingPage();
        previousPage_ = temp;
    }
}

const string &StoryboardsHandler::getPlaneDataset()
{
    return guiDataManager_.getPlaneDataset();
}

void StoryboardsHandler::setMainCallibrationParameters(const CalibrationConfiguration& paramteres)
{
    guiDataManager_.setMainCallibrationParameters(paramteres);

    if(currentPage_ == PagesType::CALLIBRATION_PAGE && callibrationPage_)
    {
        callibrationPage_->setupPage(config::UICommunicationMode::MASTER);
    }
}

void StoryboardsHandler::setRedundantCallibrationParameters(const CalibrationConfiguration& paramteres)
{
    guiDataManager_.setRedundantCallibrationParameters(paramteres);

    if(currentPage_ == PagesType::CALLIBRATION_PAGE && callibrationPage_)
    {
        callibrationPage_->setupPage(config::UICommunicationMode::REDUNDANT);
    }
}

const CalibrationConfiguration& StoryboardsHandler::getMainCallibrationParameters()
{
    return guiDataManager_.getMainCallibrationParameters();
}

const CalibrationConfiguration& StoryboardsHandler::getRedundantCallibrationParameters()
{
    return guiDataManager_.getRedundantCallibrationParameters();
}

void StoryboardsHandler::setBitsInformation(const BitsInformation& bitsInformation)
{
    if (static_cast<FeederMode>(bitsInformation.mode) == FeederMode::MASTER)
        guiDataManager_.setMainBitsInformation(bitsInformation);
    else
        guiDataManager_.setRedundantBitsInformation(bitsInformation);

    if(currentPage_ == PagesType::BITS_PAGE && bitsPage_)
    {
        bitsPage_->update();
    }
}

const BitsInformation &StoryboardsHandler::getMainBitsInformation()
{
    return guiDataManager_.getMainBitsInformation();
}

const BitsInformation &StoryboardsHandler::getRedundantBitsInformation()
{
    return guiDataManager_.getRedundantBitsInformation();
}

bool StoryboardsHandler::isSystemActive()
{
    return guiDataManager_.isSystemAcitve();
}

void StoryboardsHandler::setSystemActivation()
{
    guiDataManager_.setSystemActivation();
}

bool StoryboardsHandler::areBITSActive()
{
    return guiDataManager_.areBITSActive();
}

void StoryboardsHandler::setBITSActive()
{
    guiDataManager_.setBITSActivation();
}
