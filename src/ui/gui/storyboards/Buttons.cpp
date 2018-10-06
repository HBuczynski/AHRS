#include "Buttons.h"
#include "ui_Buttons.h"

#include <functional>
#include <config_reader/ConfigurationReader.h>
#include <config_reader/UIParameters.h>

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

void Buttons::initialize(const map<SwitchesCode, string> &names, const map<SwitchesCode, function<void()> > &callbackFunctions)
{
    initializeText(names);
    initializeSwitches(callbackFunctions);
}

void Buttons::initializeText(const map<SwitchesCode, string> &names)
{
    ui->firstButton->setText(getButtonText(SwitchesCode::FIRST_SWITCH, names).c_str());
    ui->secondButton->setText(getButtonText(SwitchesCode::SECOND_SWITCH, names).c_str());
    ui->thirdButton->setText(getButtonText(SwitchesCode::THIRD_SWITCH, names).c_str());
    ui->fourthButton->setText(getButtonText(SwitchesCode::FOURTH_SWITCH, names).c_str());
}

void Buttons::initializeSwitches(const map<SwitchesCode, function<void()> > &callbackFunctions)
{
    const function< void(SwitchState) > errorCallback = bind(&Buttons::switchError, this, std::placeholders::_1);
    const auto switchesGPIO = config::ConfigurationReader::getUISwitches(config::UI_BUTTONS_PARAMETERS_PATH.c_str());
    auto iterSwitchesGPIO = switchesGPIO.begin();

    if(callbackFunctions.size() == switchesGPIO.size())
    {
        for (const auto callbackIter : callbackFunctions)
        {
            switches_[callbackIter.first] = make_unique<SwitchHandle>((*iterSwitchesGPIO), callbackIter.first);
            switches_[callbackIter.first]->initializeCallbacks(callbackIter.second, errorCallback);
            ++iterSwitchesGPIO;
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = std::string("Buttons :: Wrong switches hardware initialization.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

string Buttons::getButtonText(SwitchesCode switchCode, map<SwitchesCode, string> switchNames)
{
    const auto firstSwitchName = switchNames.find(switchCode);
    if(firstSwitchName != switchNames.end())
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

void Buttons::switchError(peripherals::SwitchState state)
{
    if(logger_.isErrorEnable())
    {
        const string message = std::string("Buttons :: Error from button interruption, state:" + to_string((int)state));
        logger_.writeLog(LogType::ERROR_LOG, message);
    }
}