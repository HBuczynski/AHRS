#include "Buttons.h"
#include "ui_Buttons.h"

using namespace std;
using namespace utility;
using namespace peripherals;

Buttons::Buttons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Buttons),
    logger_(Logger::getInstance())
{
    ui->setupUi(this);
    setup();
}

Buttons::~Buttons()
{
    delete ui;
}

void Buttons::setup()
{
    QFont font("Arial", 15, QFont::Bold);
    ui->firstButton->setStyleSheet("QLabel { color: cyan}");
    ui->firstButton->setFont(font);
    ui->firstButton->setAlignment(Qt::AlignCenter);
    ui->firstButton->setText(" ");

    ui->secondButton->setStyleSheet("QLabel { color: cyan }");
    ui->secondButton->setFont(font);
    ui->secondButton->setAlignment(Qt::AlignCenter);
    ui->secondButton->setText(" ");

    ui->thirdButton->setStyleSheet("QLabel { color: cyan}");
    ui->thirdButton->setFont(font);
    ui->thirdButton->setAlignment(Qt::AlignCenter);
    ui->thirdButton->setText(" ");

    ui->fourthButton->setStyleSheet("QLabel { color: cyan}");
    ui->fourthButton->setFont(font);
    ui->fourthButton->setAlignment(Qt::AlignCenter);
    ui->fourthButton->setText(" ");
}

void Buttons::initialize(map<SwitchesCode, string> name, map<SwitchesCode, function<void()> > callbackFunctions)
{
    name_ = name;
    callbackFunctions_ = callbackFunctions;

    initializeText();
}

void Buttons::initializeText()
{
    ui->firstButton->setText(getButtonText(SwitchesCode::FIRST_SWITCH).c_str());
    ui->secondButton->setText(getButtonText(SwitchesCode::SECOND_SWITCH).c_str());
    ui->thirdButton->setText(getButtonText(SwitchesCode::THIRD_SWITCH).c_str());
    ui->fourthButton->setText(getButtonText(SwitchesCode::FOURTH_SWITCH).c_str());
}

string Buttons::getButtonText(SwitchesCode switchCode)
{
    const auto firstSwitchName = name_.find(switchCode);
    if(firstSwitchName != name_.end())
    {
        return firstSwitchName->second;
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = std::string("Buttons :: Wrong button code, failed code:");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return string("");
    }
}
