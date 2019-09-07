#include "ExitPage.h"
#include "ui_ExitPage.h"

#include <interfaces/gui/GUIRestartResponse.h>
#include <interfaces/gui/GUIShutdownResponse.h>

using namespace std;
using namespace utility;
using namespace peripherals;

ExitPage::ExitPage(gui::PageController* controller, QWidget *parent) :
    QWidget(parent),
    currentOption_(0),
    ui_(new Ui::ExitPage),
    controller_(controller),
    MAX_OPTIONS_NUMBER(3)
{
    ui_->setupUi(this);

    setupPage();
    highlightCurrentOption(currentOption_);
}

ExitPage::~ExitPage()
{
    if(ui_)
    {
        delete ui_;
    }
}

void ExitPage::setupPage()
{
    // Title label
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 35, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("EXIT");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    QFont options("Arial", 20, QFont::Bold);
    ui_->cancelLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->cancelLabel->setFont(options);
    ui_->cancelLabel->setText("CANCEL");
    ui_->cancelLabel->setAlignment(Qt::AlignCenter);

    ui_->restartLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->restartLabel->setFont(options);
    ui_->restartLabel->setText("RESTART");
    ui_->restartLabel->setAlignment(Qt::AlignCenter);

    ui_->exitLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->exitLabel->setFont(options);
    ui_->exitLabel->setText("SHUT DOWN");
    ui_->exitLabel->setAlignment(Qt::AlignCenter);

    labels_.push_back(ui_->cancelLabel);
    labels_.push_back(ui_->restartLabel);
    labels_.push_back(ui_->exitLabel);
}

void ExitPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "BACK";
    buttonNames[SwitchCode::SECOND_SWITCH] = "< LEFT";//"\u21E6";
    buttonNames[SwitchCode::THIRD_SWITCH] = "RIGHT >";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "SUBMIT";//"\u21E8";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&ExitPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&ExitPage::leftArrow, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&ExitPage::rightArrow, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&ExitPage::submit, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalBackToPreviousPage()), controller_, SLOT(backToPreviousPage()));
    QObject::connect(this, SIGNAL(signalRestartPage()), controller_, SLOT(setRestartPage()));
}

void ExitPage::highlightCurrentOption(uint8_t newOption)
{
    labels_[currentOption_]->setStyleSheet("QLabel { color: rgb(255,255,255); background: rgb(0,0,0);}");
    labels_[newOption]->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");

    currentOption_ = newOption;
}

void ExitPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = unique_ptr<Buttons>(new Buttons(this));
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void ExitPage::firstButton()
{
    emit signalBackToPreviousPage();
}

void ExitPage::leftArrow()
{
    int8_t tempNumber = currentOption_ - 1;

    if(tempNumber<0)
    {
        tempNumber += MAX_OPTIONS_NUMBER;
    }

    highlightCurrentOption(tempNumber);
}

void ExitPage::submit()
{
    if(currentOption_ == 0)
    {
        emit signalBackToPreviousPage();
    }
    else if(currentOption_ == 1)
    {
        communication::GUIRestartResponse restart;
        controller_->sendToMainProcess(restart.getFrameBytes());
    }
    else if(currentOption_ == 2)
    {
        communication::GUIShutdownResponse shutdown;
        controller_->sendToMainProcess(shutdown.getFrameBytes());
    }
}

void ExitPage::rightArrow()
{
    int8_t tempNumber = currentOption_ + 1;

    if(tempNumber >= MAX_OPTIONS_NUMBER)
    {
        tempNumber = tempNumber % MAX_OPTIONS_NUMBER;
    }

    highlightCurrentOption(tempNumber);
}
