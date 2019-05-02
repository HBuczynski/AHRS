#include "CalibrationState.h"

#include <iostream>

#include <utility/BytesConverter.h>

using namespace std;
using namespace config;
using namespace utility;


CalibrationState::CalibrationState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void CalibrationState::runEntryEvent()
{}

void CalibrationState::runExitEvent()
{}

void CalibrationState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- CalibrationState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    cout << "Plane name: " << getFeederData_().planeName << endl;
    imuCalibrator_.setPlane(getFeederData_().planeName);
    imuCalibrator_.initializeExternalSharedMemory();
    imuCalibrator_.startCalibration();
}

void CalibrationState::registerDataCallback(function<FeederDataContainer&()> getFeederData)
{
    getFeederData_ = getFeederData;
}

void CalibrationState::accelerometerAction(uint8_t axis, communication::AccelAction)
{
    cout << "Calib accel" << endl;
}

void CalibrationState::approveMagnetometer()
{
    cout << "Approve Mag" << endl;
}
