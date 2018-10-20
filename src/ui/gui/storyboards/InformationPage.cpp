#include "InformationPage.h"
#include "ui_InformationPage.h"
#include <interfaces/gui/GUIWindowCommand.h>

using namespace std;
using namespace utility;
using namespace peripherals;

InformationPage::InformationPage(gui::PageController *controller, QWidget *parent) :
    QWidget(parent),
    controller_(controller),
    ui_(new Ui::InformationPage)
{
    ui_->setupUi(this);
    pageSetup();

    qRegisterMetaType<std::vector<uint8_t>>("std::vector<uint8_t>");
}

InformationPage::~InformationPage()
{
    delete ui_;
}

void InformationPage::pageSetup()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 30, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("INFO");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    QFont labelFont("Arial", 15, QFont::Bold);
    ui_->lefLabel->setStyleSheet("QLabel { color : white}");
    ui_->lefLabel->setFont(labelFont);
    ui_->lefLabel->setText("CONNECTION MASTER");

    ui_->dotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel->setFont(labelFont);
    ui_->dotsLabel->setText("...........................................................................................................................................");

    QFont sqareFont("Arial", 22, QFont::Bold);
    ui_->rightLabel->setStyleSheet("QLabel { color : white}");
    ui_->rightLabel->setFont(sqareFont);
    ui_->rightLabel->setText("\u25FB\u25FB\u25FB");

    ui_->lefLabel_2->setStyleSheet("QLabel { color : white}");
    ui_->lefLabel_2->setFont(labelFont);
    ui_->lefLabel_2->setText("CONNECTION SECONDARY");

    ui_->dotsLabel_2->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_2->setFont(labelFont);
    ui_->dotsLabel_2->setText(".........................................................................................................................");

    ui_->rightLabel_2->setStyleSheet("QLabel { color : white}");
    ui_->rightLabel_2->setFont(sqareFont);
    ui_->rightLabel_2->setText("\u25FB\u25FB\u25FB");

    ui_->lefLabel_3->setStyleSheet("QLabel { color : white}");
    ui_->lefLabel_3->setFont(labelFont);
    ui_->lefLabel_3->setText("BITS MASTER");

    ui_->dotsLabel_3->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_3->setFont(labelFont);
    ui_->dotsLabel_3->setText("............................................................................................................................."
                              "..................................................................");

    ui_->rightLabel_3->setStyleSheet("QLabel { color : white}");
    ui_->rightLabel_3->setFont(sqareFont);
    ui_->rightLabel_3->setText("\u25FB\u25FB\u25FB");

    ui_->lefLabel_5->setStyleSheet("QLabel { color : white}");
    ui_->lefLabel_5->setFont(labelFont);
    ui_->lefLabel_5->setText("BITS REDUNDANT");

    ui_->dotsLabel_5->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_5->setFont(labelFont);
    ui_->dotsLabel_5->setText("............................................................................................................................."
                              "..................................................................");

    ui_->rightLabel_5->setStyleSheet("QLabel { color : white}");
    ui_->rightLabel_5->setFont(sqareFont);
    ui_->rightLabel_5->setText("\u25FB\u25FB\u25FB");


    buttons_ = make_unique<Buttons>();
    ui_->buttonLayout->addWidget(buttons_.get());
}

void InformationPage::initializeExit()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "";
    buttonNames[SwitchCode::SECOND_SWITCH] = "";
    buttonNames[SwitchCode::THIRD_SWITCH] = "";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "EXIT";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&InformationPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&InformationPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&InformationPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&InformationPage::exitButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalExitPage()), controller_, SLOT(setExitPage()));
}

void InformationPage::initializeContinue()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "";
    buttonNames[SwitchCode::SECOND_SWITCH] = "";
    buttonNames[SwitchCode::THIRD_SWITCH] = "";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "CONTINUE";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&InformationPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&InformationPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&InformationPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&InformationPage::continueButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalAHRSPage()), controller_, SLOT(setAHRSPage()));
    QObject::connect(this, SIGNAL(signalStartAcquisition(std::vector<uint8_t>)), controller_, SLOT(sendToMainProcess(std::vector<uint8_t>)));
}

void InformationPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>();
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void InformationPage::setMasterConnectionEstablished()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->rightLabel->setFont(sqareFont);
    ui_->rightLabel->setText("TRUE");
    ui_->rightLabel->setAlignment(Qt::AlignLeft);
}

void InformationPage::setMasterConnectionFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel->setStyleSheet("QLabel { color: red}");
    ui_->rightLabel->setFont(sqareFont);
    ui_->rightLabel->setText("FALSE");
    ui_->rightLabel->setAlignment(Qt::AlignLeft);
}

void InformationPage::setSecondaryConnectionEstablished()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_2->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->rightLabel_2->setFont(sqareFont);
    ui_->rightLabel_2->setText("TRUE");
    ui_->rightLabel_2->setAlignment(Qt::AlignLeft);
}

void InformationPage::setSecondaryConnectionFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_2->setStyleSheet("QLabel { color: red}");
    ui_->rightLabel_2->setFont(sqareFont);
    ui_->rightLabel_2->setText("FALSE");
    ui_->rightLabel_2->setAlignment(Qt::AlignLeft);
}

void InformationPage::setBITSMaster()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_3->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->rightLabel_3->setFont(sqareFont);
    ui_->rightLabel_3->setText("TRUE");
    ui_->rightLabel_3->setAlignment(Qt::AlignLeft);
}

void InformationPage::setBITSMasterFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_3->setStyleSheet("QLabel { color: red}");
    ui_->rightLabel_3->setFont(sqareFont);
    ui_->rightLabel_3->setText("FALSE");
    ui_->rightLabel_3->setAlignment(Qt::AlignLeft);
}


void InformationPage::setBITSRedundant()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_5->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->rightLabel_5->setFont(sqareFont);
    ui_->rightLabel_5->setText("TRUE");
    ui_->rightLabel_5->setAlignment(Qt::AlignLeft);
}

void InformationPage::setBITRedundantFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_5->setStyleSheet("QLabel { color: red}");
    ui_->rightLabel_5->setFont(sqareFont);
    ui_->rightLabel_5->setText("FALSE");
    ui_->rightLabel_5->setAlignment(Qt::AlignLeft);;
}

void InformationPage::firstButton()
{

}

void InformationPage::secondButton()
{

}

void InformationPage::thirdButton()
{

}

void InformationPage::exitButton()
{
    emit signalExitPage();
}

void InformationPage::continueButton()
{
    emit signalAHRSPage();

    communication::GUIWindowCommand command(communication::WindowType::AHRS);

    emit signalStartAcquisition(command.getFrameBytes());
}