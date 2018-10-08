#include "Buttons.h"
#include "ui_Buttons.h"

#include <functional>
#include <config_reader/ConfigurationReader.h>
#include <config_reader/UIParameters.h>

#include <hal/include/PIGPIOInitializer.h>

using namespace std;
using namespace utility;
using namespace peripherals;

Buttons::Buttons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Buttons),
    logger_(Logger::getInstance())
{
    hardware::PIGPIOInitializer::initialize();
    ui->setupUi(this);
    setup();
}

Buttons::~Buttons()
{
    hardware::PIGPIOInitializer::terminate();
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

void Buttons::initialize(const map<SwitchCode, string> &names, const map<SwitchCode, function<void()> > &callbackFunctions)
{
    initializeText(names);
    initializeSwitches(callbackFunctions);
}

void Buttons::initializeText(const map<SwitchCode, string> &names)
{
    ui->firstButton->setText(getButtonText(SwitchCode::FIRST_SWITCH, names).c_str());
    ui->secondButton->setText(getButtonText(SwitchCode::SECOND_SWITCH, names).c_str());
    ui->thirdButton->setText(getButtonText(SwitchCode::THIRD_SWITCH, names).c_str());
    ui->fourthButton->setText(getButtonText(SwitchCode::FOURTH_SWITCH, names).c_str());
}

void Buttons::initializeSwitches(const map<SwitchCode, function<void()> > &callbackFunctions)
{
    const function< void(SwitchCode, SwitchState) > errorCallback = bind(&Buttons::switchError, this, std::placeholders::_1, std::placeholders::_2);
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

string Buttons::getButtonText(SwitchCode switchCode, map<SwitchCode, string> switchNames)
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

void Buttons::switchError(SwitchCode code, SwitchState state)
{
    if(logger_.isErrorEnable())
    {
        const string message = string("Buttons :: Error from button interruption, Switch number:" + to_string((int)code)) +
                string(" Switch state: ") + to_string((int)state);
        logger_.writeLog(LogType::ERROR_LOG, message);
    }
}