#include "ExitPage.h"
#include "ui_ExitPage.h"

using namespace std;
using namespace utility;
using namespace peripherals;

ExitPage::ExitPage(/*gui::PageController* controller,*/ QWidget *parent) :
    QWidget(parent),
    currentOption_(0),
    ui(new Ui::ExitPage),
    //controller_(controller),
    MAX_OPTIONS_NUMBER(3)
{
    ui->setupUi(this);

    cout << "In exiit page constr" << endl;
    setupPage();
    highlightCurrentOption(currentOption_);
}

ExitPage::~ExitPage()
{
    delete ui;

    if(buttons)
    {
        delete buttons;
    }
}

void ExitPage::setupPage()
{
    // Title label
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 35, QFont::Bold);
    ui->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui->titleLabel->setFont(font);
    ui->titleLabel->setText("EXIT");
    ui->titleLabel->setAlignment(Qt::AlignCenter);

    QFont options("Arial", 20, QFont::Bold);
    ui->cancelLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui->cancelLabel->setFont(options);
    ui->cancelLabel->setText("CANCEL");
    ui->cancelLabel->setAlignment(Qt::AlignCenter);

    ui->restartLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui->restartLabel->setFont(options);
    ui->restartLabel->setText("RESTART");
    ui->restartLabel->setAlignment(Qt::AlignCenter);

    ui->exitLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui->exitLabel->setFont(options);
    ui->exitLabel->setText("QUIT");
    ui->exitLabel->setAlignment(Qt::AlignCenter);



    labels_.push_back(ui->cancelLabel);
    labels_.push_back(ui->restartLabel);
    labels_.push_back(ui->exitLabel);
}

void ExitPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "";
    buttonNames[SwitchCode::SECOND_SWITCH] = "\u21E6";
    buttonNames[SwitchCode::THIRD_SWITCH] = "SUBMIT";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "\u21E8";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&ExitPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&ExitPage::leftArrow, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&ExitPage::submit, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&ExitPage::rightArrow, this);

    initializeButtons(buttonNames, callbackFunctions);
}

void ExitPage::highlightCurrentOption(uint8_t newOption)
{
    labels_[currentOption_]->setStyleSheet("QLabel { color: rgb(255,255,255); background: rgb(0,0,0);}");

    labels_[newOption]->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");

    currentOption_ = newOption;
}

void ExitPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    cout << "Buttons init" << endl;
    buttons = new Buttons();
    buttons->initialize(name, callbackFunctions);

    cout << "After buttons init" << endl;

    ui->buttonLayout->addWidget(buttons);

    cout << "After adding buttons to layout." << endl;
}

void ExitPage::firstButton()
{

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
        //controller_->setAHRSPage();
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
