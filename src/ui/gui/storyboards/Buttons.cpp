#include "Buttons.h"
#include "ui_Buttons.h"

#include <functional>
#include <config_reader/ConfigurationReader.h>
#include <config_reader/UIParameters.h>

#include "../KeyboardHandler.h"

using namespace std;
using namespace utility;
using namespace peripherals;

Buttons::Buttons(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::Buttons),
    logger_(Logger::getInstance())
{
    ui_->setupUi(this);
    setup();
}

Buttons::~Buttons()
{
    if(ui_)
    {
        delete ui_;
    }
}

void Buttons::setup()
{
    QFont font("Arial", 15, QFont::Bold);
    ui_->firstButton->setStyleSheet("QLabel { color: cyan}");
    ui_->firstButton->setFont(font);
    ui_->firstButton->setAlignment(Qt::AlignCenter);
    ui_->firstButton->setText(" ");

    ui_->secondButton->setStyleSheet("QLabel { color: cyan }");
    ui_->secondButton->setFont(font);
    ui_->secondButton->setAlignment(Qt::AlignCenter);
    ui_->secondButton->setText(" ");

    ui_->thirdButton->setStyleSheet("QLabel { color: cyan}");
    ui_->thirdButton->setFont(font);
    ui_->thirdButton->setAlignment(Qt::AlignCenter);
    ui_->thirdButton->setText(" ");

    ui_->fourthButton->setStyleSheet("QLabel { color: cyan}");
    ui_->fourthButton->setFont(font);
    ui_->fourthButton->setAlignment(Qt::AlignCenter);
    ui_->fourthButton->setText(" ");
}

void Buttons::initialize(const map<SwitchCode, string> &names, const map<SwitchCode, function<void()> > &callbackFunctions)
{
    initializeText(names);
    initializeSwitches(callbackFunctions);
}

void Buttons::initializeText(const map<SwitchCode, string> &names)
{
    ui_->firstButton->setText(getButtonText(SwitchCode::FIRST_SWITCH, names).c_str());
    ui_->secondButton->setText(getButtonText(SwitchCode::SECOND_SWITCH, names).c_str());
    ui_->thirdButton->setText(getButtonText(SwitchCode::THIRD_SWITCH, names).c_str());
    ui_->fourthButton->setText(getButtonText(SwitchCode::FOURTH_SWITCH, names).c_str());
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

#ifdef VIRTUAL_BOARD
            switches_[callbackIter.first] = make_unique<KeyboardHandler>(this, (*iterSwitchesGPIO), callbackIter.first);
#else
            switches_[callbackIter.first] = make_unique<RPISwitchHandle>((*iterSwitchesGPIO), callbackIter.first);
#endif

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