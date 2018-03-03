#include <exception>
#include "SwitchesManager.h"
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace peripherals;

SwitchesManager::SwitchesManager()
{}

SwitchesManager::~SwitchesManager()
{}

void SwitchesManager::initialize()
{
    getSwitchesParametersFromConfig();
}

const std::map<SwitchesCode, std::shared_ptr<SwitchesHandle> > &SwitchesManager::getSwitches() const
{
    return switches_;
}

void SwitchesManager::getSwitchesParametersFromConfig()
{
    //config::ConfigurationReader configurationReader;
}

void SwitchesManager::initializeSwitches(SwitchesCode code, hardware::GPIO gpio)
{
    switch(code)
    {
        case SwitchesCode::BOTTOM_SWITCH :
            switches_[BOTTOM_SWITCH] = make_shared<SwitchesHandle>(gpio);
            break;

        case SwitchesCode::CANCEL_SWITCH :
            switches_[CANCEL_SWITCH] = make_shared<SwitchesHandle>(gpio);
            break;

        case SwitchesCode::OK_SWITCH :
            switches_[OK_SWITCH] = make_shared<SwitchesHandle>(gpio);
            break;

        case SwitchesCode::UP_SWITCH :
            switches_[UP_SWITCH] = make_shared<SwitchesHandle>(gpio);
            break;

        default:
             throw invalid_argument("Invalid switch code.");
    }
}
