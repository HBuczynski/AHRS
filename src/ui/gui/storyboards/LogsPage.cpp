#include "LogsPage.h"
#include "ui_LogsPage.h"

using namespace std;
using namespace peripherals;

LogsPage::LogsPage(gui::PageController* controller, QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::LogsPage),
    controller_(controller)
{
    ui_->setupUi(this);
    setupPage();
}

LogsPage::~LogsPage()
{
    delete ui_;
}

void LogsPage::setupPage()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 30, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("LOGS");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);
}

void LogsPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "";
    buttonNames[SwitchCode::SECOND_SWITCH] = "";
    buttonNames[SwitchCode::THIRD_SWITCH] = "";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "< BACK";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&LogsPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&LogsPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&LogsPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&LogsPage::fourthButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalBackPage()), controller_, SLOT(setAHRSPage()));
}

void LogsPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = unique_ptr<Buttons>(new Buttons(this));
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void LogsPage::firstButton()
{

}

void LogsPage::secondButton()
{

}

void LogsPage::thirdButton()
{

}

void LogsPage::fourthButton()
{
    emit signalBackPage();
}
