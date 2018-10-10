#include "MainPage.h"
#include "ui_MainPage.h"

using namespace std;
using namespace peripherals;

MainPage::MainPage(gui::PageController* controller, QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::MainPage),
    controller_(controller)
{
    ui_->setupUi(this);
    setupPage();
}

MainPage::~MainPage()
{
    delete ui_;
}

void MainPage::setupPage()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 30, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("MAIN PAGE");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);
}

void MainPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "";
    buttonNames[SwitchCode::SECOND_SWITCH] = "";
    buttonNames[SwitchCode::THIRD_SWITCH] = "";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "< BACK";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&MainPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&MainPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&MainPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&MainPage::fourthButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalBackPage()), controller_, SLOT(setAHRSPage()));
}

void MainPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>();
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void MainPage::firstButton()
{

}

void MainPage::secondButton()
{

}

void MainPage::thirdButton()
{

}

void MainPage::fourthButton()
{
    emit signalBackPage();
}