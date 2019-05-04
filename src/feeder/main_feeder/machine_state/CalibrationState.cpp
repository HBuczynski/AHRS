#include "CalibrationState.h"

#include <iostream>

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;


CalibrationState::CalibrationState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void CalibrationState::runEntryEvent()
{}

void CalibrationState::runExitEvent()
{
    calibrationManager_.stopCalibration();
}

void CalibrationState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- CalibrationState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    calibrationManager_.setPlane(getFeederData_().planeName);
    calibrationManager_.initializeExternalSharedMemory();
    calibrationManager_.startCalibration();
}

void CalibrationState::registerDataCallback(function<FeederDataContainer&()> getFeederData)
{
    getFeederData_ = getFeederData;
}

void CalibrationState::accelerometerAction(uint8_t axis, communication::AccelAction action)
{
    calibrationManager_.accelerometerAction(axis, action);
}

void CalibrationState::approveMagnetometer()
{
    calibrationManager_.approveMagnetometer();
}
