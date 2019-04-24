#include "MainPage.h"
#include "ui_MainPage.h"

using namespace std;
using namespace peripherals;

MainPage::MainPage(gui::PageController* controller, QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::MainPage),
    controller_(controller),
    MAX_OPTIONS_NUMBER(4)
{
    ui_->setupUi(this);
    setupPage();

    if(controller_->isSystemActive())
        currentOption_= 0;
    else
        currentOption_ = 1;

    highlightCurrentOption(currentOption_);
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

    QFont font2("Arial", 20, QFont::Bold);
    QFont font3("Arial", 15, QFont::Bold);

    if(controller_->isSystemActive())
    {
        ui_->ahrsLabel->setStyleSheet("QLabel { color: rgb(255,255, 255)}");
        ui_->ahrsLabel->setFont(font2);
        ui_->ahrsLabel->setText("AHRS");
        ui_->ahrsLabel->setAlignment(Qt::AlignCenter);

        ui_->bitLabel->setStyleSheet("QLabel { color: rgb(255,255, 255)}");
        ui_->bitLabel->setFont(font2);
        ui_->bitLabel->setText("BITS INFO");
        ui_->bitLabel->setAlignment(Qt::AlignCenter);

        ui_->notesLabel->setStyleSheet("QLabel { color: rgb(255,0, 0)}");
        ui_->notesLabel->setFont(font3);
        ui_->notesLabel->setText("");
        ui_->notesLabel->setAlignment(Qt::AlignLeft);
    }
    else
    {
        ui_->ahrsLabel->setStyleSheet("QLabel { color: rgb(105,105, 105)}");
        ui_->ahrsLabel->setFont(font2);
        ui_->ahrsLabel->setText("AHRS");
        ui_->ahrsLabel->setAlignment(Qt::AlignCenter);

        ui_->bitLabel->setStyleSheet("QLabel { color: rgb(105,105, 105)}");
        ui_->bitLabel->setFont(font2);
        ui_->bitLabel->setText("BITS INFO");
        ui_->bitLabel->setAlignment(Qt::AlignCenter);

        ui_->notesLabel->setStyleSheet("QLabel { color: rgb(255,0, 0)}");
        ui_->notesLabel->setFont(font3);
        ui_->notesLabel->setText("NOTE: Set appropriate plane settings !!");
        ui_->notesLabel->setAlignment(Qt::AlignLeft);
    }

    ui_->planeLabel->setStyleSheet("QLabel { color: rgb(255,255, 255)}");
    ui_->planeLabel->setFont(font2);
    ui_->planeLabel->setText("PLANE SETTINGS");
    ui_->planeLabel->setAlignment(Qt::AlignCenter);

    ui_->exitLabel->setStyleSheet("QLabel { color: rgb(255,255, 255)}");
    ui_->exitLabel->setFont(font2);
    ui_->exitLabel->setText("QUIT");
    ui_->exitLabel->setAlignment(Qt::AlignCenter);

    labels_.push_back(ui_->ahrsLabel);
    labels_.push_back(ui_->planeLabel);
    labels_.push_back(ui_->bitLabel);
    labels_.push_back(ui_->exitLabel);
}

void MainPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "< BACK";
    buttonNames[SwitchCode::SECOND_SWITCH] = "DOWN";
    buttonNames[SwitchCode::THIRD_SWITCH] = "UP";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "SELECT";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&MainPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&MainPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&MainPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&MainPage::fourthButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalBackPage()), controller_, SLOT(backToPreviousPage()));
    QObject::connect(this, SIGNAL(signalAHRSPage()), controller_, SLOT(setAHRSPage()));
    QObject::connect(this, SIGNAL(signalPlaneSettingsPage()), controller_, SLOT(setPlaneSettingPage()));
    QObject::connect(this, SIGNAL(signalBitsInfoPage()), controller_, SLOT(setPlaneSettingPage()));
    QObject::connect(this, SIGNAL(signalExitPage()), controller_, SLOT(setExitPage()));
}

void MainPage::highlightCurrentOption(uint8_t newOption)
{
    labels_[currentOption_]->setStyleSheet("QLabel { color: rgb(255,255,255); background: rgb(0,0,0);}");
    labels_[newOption]->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");

    currentOption_ = newOption;
}

void MainPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>(this);
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void MainPage::firstButton()
{
    emit signalBackPage();
}

void MainPage::secondButton()
{
    int8_t tempNumber = currentOption_ + 1;

    if(tempNumber >= MAX_OPTIONS_NUMBER)
        tempNumber = tempNumber % MAX_OPTIONS_NUMBER;

    const auto type = static_cast<MainPageOptions>(tempNumber);
    if(!controller_->isSystemActive() && (type == MainPageOptions::AHRS || type == MainPageOptions::BITS_INFO))
    {
        tempNumber += 1;

        if(tempNumber >= MAX_OPTIONS_NUMBER)
            tempNumber = tempNumber % MAX_OPTIONS_NUMBER;
    }

    highlightCurrentOption(tempNumber);
}

void MainPage::thirdButton()
{
    int8_t tempNumber = currentOption_ - 1;

    if(tempNumber<0)
        tempNumber += MAX_OPTIONS_NUMBER;

    const auto type = static_cast<MainPageOptions>(tempNumber);

    if(!controller_->isSystemActive() && (type == MainPageOptions::AHRS || type == MainPageOptions::BITS_INFO))
    {
        tempNumber -= 1;

        if(tempNumber<0)
            tempNumber += MAX_OPTIONS_NUMBER;
    }

    highlightCurrentOption(tempNumber);
}

void MainPage::fourthButton()
{
    const auto type =static_cast<MainPageOptions>(currentOption_);

    switch (type)
    {
        case MainPageOptions::AHRS :
        {
            emit signalAHRSPage();
            break;
        }
        case MainPageOptions::PLANE_SETTINGS :
        {
            emit signalPlaneSettingsPage();
            break;
        }
        case MainPageOptions::BITS_INFO :
        {
            emit signalBitsInfoPage();
            break;
        }
        case MainPageOptions::EXIT :
        {
            emit signalExitPage();
            break;
        }
        default:
            break;
    }
}
