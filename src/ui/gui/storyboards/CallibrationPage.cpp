#include "CallibrationPage.h"
#include "ui_CallibrationPage.h"

using namespace std;
using namespace peripherals;

CallibrationPage::CallibrationPage(gui::PageController* controller, QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::CallibrationPage),
    controller_(controller)
{
    ui_->setupUi(this);
    setupPage();
}

CallibrationPage::~CallibrationPage()
{
    delete ui_;
}

void CallibrationPage::setupPage()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 30, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("CALLIBRATION");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);
}

void CallibrationPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "";
    buttonNames[SwitchCode::SECOND_SWITCH] = "";
    buttonNames[SwitchCode::THIRD_SWITCH] = "";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "< BACK";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&CallibrationPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&CallibrationPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&CallibrationPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&CallibrationPage::fourthButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalBackPage()), controller_, SLOT(backToPreviousPage()));
}

void CallibrationPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>(this);
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void CallibrationPage::firstButton()
{

}

void CallibrationPage::secondButton()
{

}

void CallibrationPage::thirdButton()
{

}

void CallibrationPage::fourthButton()
{
    emit signalBackPage();
}

