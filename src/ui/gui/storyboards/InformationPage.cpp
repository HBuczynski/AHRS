#include "InformationPage.h"
#include "ui_InformationPage.h"
#include <interfaces/gui/GUIWindowResponse.h>

#include <interfaces/wireless_commands/StartAcquisitionCommand.h>
#include <interfaces/wireless_commands/BITSDataCommand.h>
#include <interfaces/gui/GUIWirelessComWrapperResponse.h>

#define PASSED 25
#define FAILED 42

using namespace std;
using namespace utility;
using namespace peripherals;
using namespace communication;

InformationPage::InformationPage(gui::PageController *controller, QWidget *parent) :
    QWidget(parent),
    timerInterrupt_("GUIInfo"),
    controller_(controller),
    ui_(new Ui::InformationPage)
{
    ui_->setupUi(this);
    pageSetup();
    update();

    timerInterrupt_.startPeriodic(USER_UPDATE_INTERVAL_MS, this);
}

InformationPage::~InformationPage()
{
    timerInterrupt_.stop();
    delete ui_;
}

void InformationPage::pageSetup()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 30, QFont::Bold);
    QFont labelFont("Arial", 20, QFont::Bold);
    QFont sqareFont("Arial", 22, QFont::Bold);

    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("BITS");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);


    ui_->masterLabel->setStyleSheet("QLabel { color : rgb(51,255,0)}");
    ui_->masterLabel->setFont(labelFont);
    ui_->masterLabel->setText("MASTER");

    ui_->m_comLabel->setStyleSheet("QLabel { color : white}");
    ui_->m_comLabel->setFont(labelFont);
    ui_->m_comLabel->setText("COMMUNICATION");

    ui_->dotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel->setFont(labelFont);
    ui_->dotsLabel->setText("...............................................................");

    ui_->m_comValue->setStyleSheet("QLabel { color : white}");
    ui_->m_comValue->setFont(sqareFont);
    ui_->m_comValue->setText("\u25FB\u25FB\u25FB");

    ui_->m_imuLabel->setStyleSheet("QLabel { color : white}");
    ui_->m_imuLabel->setFont(labelFont);
    ui_->m_imuLabel->setText("IMU");

    ui_->dotsLabel_2->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_2->setFont(labelFont);
    ui_->dotsLabel_2->setText("...........................................................................................................................................");

    ui_->m_imuValue->setStyleSheet("QLabel { color : white}");
    ui_->m_imuValue->setFont(sqareFont);
    ui_->m_imuValue->setText("\u25FB\u25FB\u25FB");

    ui_->m_gpsLabel->setStyleSheet("QLabel { color : white}");
    ui_->m_gpsLabel->setFont(labelFont);
    ui_->m_gpsLabel->setText("GPS");

    ui_->dotsLabel_3->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_3->setFont(labelFont);
    ui_->dotsLabel_3->setText("...........................................................................................................................................");

    ui_->m_gpsValue->setStyleSheet("QLabel { color : white}");
    ui_->m_gpsValue->setFont(sqareFont);
    ui_->m_gpsValue->setText("\u25FB\u25FB\u25FB");



    ui_->redundantLabel->setStyleSheet("QLabel { color : rgb(51,255,0)}");
    ui_->redundantLabel->setFont(labelFont);
    ui_->redundantLabel->setText("REDUNDANT");

    ui_->r_comLabel->setStyleSheet("QLabel { color : white}");
    ui_->r_comLabel->setFont(labelFont);
    ui_->r_comLabel->setText("COMMUNICATION");

    ui_->dotsLabel_5->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_5->setFont(labelFont);
    ui_->dotsLabel_5->setText("...............................................................");

    ui_->r_comValue->setStyleSheet("QLabel { color : white}");
    ui_->r_comValue->setFont(sqareFont);
    ui_->r_comValue->setText("\u25FB\u25FB\u25FB");

    ui_->r_imuLabel->setStyleSheet("QLabel { color : white}");
    ui_->r_imuLabel->setFont(labelFont);
    ui_->r_imuLabel->setText("IMU");

    ui_->dotsLabel_7->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_7->setFont(labelFont);
    ui_->dotsLabel_7->setText("...........................................................................................................................................");

    ui_->r_imuValue->setStyleSheet("QLabel { color : white}");
    ui_->r_imuValue->setFont(sqareFont);
    ui_->r_imuValue->setText("\u25FB\u25FB\u25FB");

    ui_->r_gpsLabel->setStyleSheet("QLabel { color : white}");
    ui_->r_gpsLabel->setFont(labelFont);
    ui_->r_gpsLabel->setText("GPS");

    ui_->dotsLabel_6->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_6->setFont(labelFont);
    ui_->dotsLabel_6->setText("...........................................................................................................................................");

    ui_->r_gpsValue->setStyleSheet("QLabel { color : white}");
    ui_->r_gpsValue->setFont(sqareFont);
    ui_->r_gpsValue->setText("\u25FB\u25FB\u25FB");

    buttons_ = make_unique<Buttons>(this);
    ui_->buttonLayout->addWidget(buttons_.get());
}

void InformationPage::initialize()
{
    map<SwitchCode, string> buttonNames;

    if(masterBitsInformation_.progress == 1 && redundantBitsInformation_.progress == 1)
    {
        buttonNames[SwitchCode::FIRST_SWITCH] = "";
        buttonNames[SwitchCode::SECOND_SWITCH] = "";
        buttonNames[SwitchCode::THIRD_SWITCH] = "MAIN";
        buttonNames[SwitchCode::FOURTH_SWITCH] = "<AHRS>";
    }
    else
    {
        buttonNames[SwitchCode::FIRST_SWITCH] = "";
        buttonNames[SwitchCode::SECOND_SWITCH] = "";
        buttonNames[SwitchCode::THIRD_SWITCH] = " ";
        buttonNames[SwitchCode::FOURTH_SWITCH] = "MAIN";
    }

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&InformationPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&InformationPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&InformationPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&InformationPage::fourthButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalAHRSPage()), controller_, SLOT(setAHRSPage()));
    QObject::connect(this, SIGNAL(signalMainPage()), controller_, SLOT(setMenuPage()));
    QObject::connect(this, SIGNAL(signalStartAcquisition(std::vector<uint8_t>)), controller_, SLOT(sendToMainProcess(std::vector<uint8_t>)));
}

void InformationPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>(this);
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void InformationPage::update()
{
    cout << "LOG 1" << endl;

    masterBitsInformation_ = controller_->getMainBitsInformation();
    cout << "LOG 1a" << endl;
    redundantBitsInformation_ = controller_->getRedundantBitsInformation();

    cout << "LOG 2" << endl;

    if(masterBitsInformation_.progress && redundantBitsInformation_.progress)
        timerInterrupt_.stop();

    if (masterBitsInformation_.communication == PASSED)
        setMasterConnectionEstablished();
    if (masterBitsInformation_.communication == FAILED)
        setMasterConnectionFailed();
    if (redundantBitsInformation_.communication == PASSED)
        setSecondaryConnectionEstablished();
    if (redundantBitsInformation_.communication == FAILED)
        setSecondaryConnectionFailed();

    if (masterBitsInformation_.gps == PASSED)
        setGPSMaster();
    if (masterBitsInformation_.gps == FAILED)
        setGPSMasterFailed();
    if (redundantBitsInformation_.gps == PASSED)
        setGPSRedundant();
    if (redundantBitsInformation_.gps == FAILED)
        setGPSRedundantFailed();

    if (masterBitsInformation_.imu == PASSED)
        setIMUMaster();
    if (masterBitsInformation_.imu == FAILED)
        setIMUSMasterFailed();
    if (redundantBitsInformation_.imu == PASSED)
        setIMURedundant();
    if (redundantBitsInformation_.imu == FAILED)
        setIMURedundantFailed();

    initialize();
}

void InformationPage::interruptNotification(timer_t timerID)
{
    BITSDataCommand dataCommand;
    GUIWirelessComWrapperResponse response(config::UICommunicationMode::MASTER, dataCommand.getFrameBytes());
    controller_->sendToMainProcess(response.getFrameBytes());

    GUIWirelessComWrapperResponse response2(config::UICommunicationMode::REDUNDANT, dataCommand.getFrameBytes());
    controller_->sendToMainProcess(response2.getFrameBytes());
}

void InformationPage::setMasterConnectionEstablished()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->m_comValue->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->m_comValue->setFont(sqareFont);
    ui_->m_comValue->setText("TRUE");
    ui_->m_comValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setMasterConnectionFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->m_comValue->setStyleSheet("QLabel { color: red}");
    ui_->m_comValue->setFont(sqareFont);
    ui_->m_comValue->setText("FALSE");
    ui_->m_comValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setSecondaryConnectionEstablished()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->r_comValue->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->r_comValue->setFont(sqareFont);
    ui_->r_comValue->setText("TRUE");
    ui_->r_comValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setSecondaryConnectionFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->r_comValue->setStyleSheet("QLabel { color: red}");
    ui_->r_comValue->setFont(sqareFont);
    ui_->r_comValue->setText("FALSE");
    ui_->r_comValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setGPSMaster()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->m_gpsValue->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->m_gpsValue->setFont(sqareFont);
    ui_->m_gpsValue->setText("TRUE");
    ui_->m_gpsValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setGPSMasterFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->m_gpsValue->setStyleSheet("QLabel { color: red}");
    ui_->m_gpsValue->setFont(sqareFont);
    ui_->m_gpsValue->setText("FALSE");
    ui_->m_gpsValue->setAlignment(Qt::AlignLeft);
}


void InformationPage::setGPSRedundant()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->r_gpsValue->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->r_gpsValue->setFont(sqareFont);
    ui_->r_gpsValue->setText("TRUE");
    ui_->r_gpsValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setGPSRedundantFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->r_gpsValue->setStyleSheet("QLabel { color: red}");
    ui_->r_gpsValue->setFont(sqareFont);
    ui_->r_gpsValue->setText("FALSE");
    ui_->r_gpsValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setIMUMaster()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->m_imuValue->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->m_imuValue->setFont(sqareFont);
    ui_->m_imuValue->setText("TRUE");
    ui_->m_imuValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setIMUSMasterFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->m_imuValue->setStyleSheet("QLabel { color: red}");
    ui_->m_imuValue->setFont(sqareFont);
    ui_->m_imuValue->setText("FALSE");
    ui_->m_imuValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setIMURedundant()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->r_imuValue->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->r_imuValue->setFont(sqareFont);
    ui_->r_imuValue->setText("TRUE");
    ui_->r_imuValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::setIMURedundantFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->r_imuValue->setStyleSheet("QLabel { color: red}");
    ui_->r_imuValue->setFont(sqareFont);
    ui_->r_imuValue->setText("FALSE");
    ui_->r_imuValue->setAlignment(Qt::AlignLeft);
}

void InformationPage::firstButton()
{}

void InformationPage::secondButton()
{}

void InformationPage::thirdButton()
{
    if( masterBitsInformation_.progress == 1)
    {
        emit signalMainPage();
    }
}

void InformationPage::fourthButton()
{
    if( masterBitsInformation_.progress == 1 && redundantBitsInformation_.progress == 1)
    {
        controller_->setSystemActivation();

        communication::GUIWindowResponse command(PagesType::AHRS_PAGE);
        auto packet = command.getFrameBytes();
        controller_->sendToMainProcess(packet);

        emit signalAHRSPage();
    }
    else
    {
        emit signalMainPage();
    }
}
