#include "UIScheduler.h"

#include "machine_state/UIIdleState.h"
#include "machine_state/UILaunchState.h"
#include "machine_state/UIConnectionState.h"
#include "machine_state/UISettingState.h"
#include "machine_state/UICallibrationState.h"
#include "machine_state/UIBitState.h"
#include "machine_state/UIAcquisitionState.h"
#include "machine_state/UIFaultManagementState.h"
#include "machine_state/UIErrorState.h"

#include <functional>

using namespace std;
using namespace main_process;

UIScheduler::UIScheduler()
{
    create();
}

void UIScheduler::create()
{
    auto idleState = make_shared<UIIdleState>("Idle");
    states_["Idle"] = idleState;
    auto launchState = make_shared<UILaunchState>("LaunchState", idleState);
    states_["LaunchState"] = launchState;
    auto connectionState = make_shared<UIConnectionState>("ConnectionState", idleState);
    states_["ConnectionState"] = connectionState;
    auto errorState = make_shared<UIErrorState>("ErrorState", idleState);
    states_["ErrorState"] = errorState;
    auto settingsState = make_shared<UISettingState>("SettingState", idleState);
    states_["SettingState"] = settingsState;
    auto calibrationState = make_shared<UICallibrationState>("CallibrationState", idleState);
    states_["CallibrationState"] = calibrationState;
    auto bitState = make_shared<UIBitState>("BitState", idleState);
    states_["BitState"] = bitState;
    auto acquisitionState = make_shared<UIAcquisitionState>("AcquisitionState", idleState);
    states_["AcquisitionState"] = acquisitionState;
    auto faultManagementState = make_shared<UIFaultManagementState>("FaultManagementState", idleState);
    states_["FaultManagementState"] = faultManagementState;

    /*Define transition table */
    hsm::TransitionTable transitionTable({
            {launchState,                   hsm::Event{"CONNECT"},            connectionState},
            {connectionState,               hsm::Event{"SET_SETTINGS"},       settingsState},
            {connectionState,               hsm::Event{"CONN_ERROR"},         faultManagementState},
            {settingsState,                 hsm::Event{"CALIBRATE"},          calibrationState},
            {calibrationState,              hsm::Event{"PERFORM_BIT"},        bitState},
            {bitState,                      hsm::Event{"DATA_ACQUISITION"},   acquisitionState},
            {acquisitionState,              hsm::Event{"ABORT"},              faultManagementState},
            {faultManagementState,          hsm::Event{"RESTORE"},            acquisitionState},
            {faultManagementState,          hsm::Event{"ERROR"},              errorState},
            {faultManagementState,          hsm::Event{"RECONNECT"},          connectionState},
    });

    uiApplicationManager_ = make_shared<UIApplicationManager>("UIApplicationManager", transitionTable, idleState);
}

bool UIScheduler::initialize()
{
    function<void(std::vector<uint8_t>)> sendToGUI = bind(&UIApplicationManager::sendToGUIProcess, uiApplicationManager_.get(), std::placeholders::_1);
    function<void(std::vector<uint8_t>, config::UICommunicationMode)> sendToExternalProcess = bind(&UIApplicationManager::sendToExternalCommunicationProcess,
                                                                                                    uiApplicationManager_.get(), std::placeholders::_1, std::placeholders::_2);

    static_pointer_cast<UILaunchState, hsm::State>(states_["LaunchState"])->registerCallbackToGUI(sendToGUI);
    static_pointer_cast<UIConnectionState, hsm::State>(states_["ConnectionState"])->registerCallbackToGUI(sendToGUI);
    static_pointer_cast<UIConnectionState, hsm::State>(states_["SettingState"])->registerCallbackToGUI(sendToGUI);

    return uiApplicationManager_->initialize();
}

void UIScheduler::run()
{
    uiApplicationManager_->startHSM();
    uiApplicationManager_->startUISystem();
}