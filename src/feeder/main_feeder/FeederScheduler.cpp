#include "FeederScheduler.h"

#include "machine_state/FeederIdleState.h"
#include "machine_state/CalibrationState.h"
#include "machine_state/InitConnectionState.h"
#include "machine_state/MainAcqState.h"
#include "machine_state/MainErrorState.h"
#include "machine_state/MainFaultManagementState.h"
#include "machine_state/PerformBitState.h"
#include "machine_state/RedundantAcqState.h"
#include "machine_state/RegisterUserState.h"
#include "machine_state/SettingsState.h"

using namespace std;
using namespace main_process;

FeederScheduler::FeederScheduler()
{
    create();
}

void FeederScheduler::create()
{
    auto idleState = make_shared<FeederIdleState>("Idle");
    states_["Idle"] = idleState;
    auto calibrationState = make_shared<CalibrationState>("CalibrationState", idleState);
    states_["CalibrationState"] = calibrationState;
    auto connectionState = make_shared<InitConnectionState>("ConnectionState", idleState);
    states_["ConnectionState"] = connectionState;
    auto mainAcqState = make_shared<MainAcqState>("MainAcqState", idleState);
    states_["MainAcqState"] = mainAcqState;
    auto mainErrorState = make_shared<MainErrorState>("MainErrorState", idleState);
    states_["MainErrorState"] = mainErrorState;
    auto mainFaultManagementState = make_shared<MainFaultManagementState>("MainFaultManagementState", idleState);
    states_["MainFaultManagementState"] = mainFaultManagementState;
    auto performBitState = make_shared<PerformBitState>("PerformBitState", idleState);
    states_["PerformBitState"] = performBitState;
    auto redundantAcqState = make_shared<RedundantAcqState>("RedundantAcqState", idleState);
    states_["RedundantAcqState"] = redundantAcqState;
    auto registerUserState = make_shared<RegisterUserState>("RegisterUserState", idleState);
    states_["RegisterUserState"] = registerUserState;
    auto settingsState = make_shared<SettingsState>("SettingsState", idleState);
    states_["SettingsState"] = settingsState;


    /*Define transition table */
    hsm::TransitionTable transitionTable({
             {connectionState,                      hsm::Event{"RUN_REGISTARTION"},             registerUserState},
             {registerUserState,                    hsm::Event{"GET_SETTINGS"},                 settingsState},
             {settingsState,                        hsm::Event{"RUN_CALLIBRATION"},             calibrationState},
             {calibrationState,                     hsm::Event{"CHECK_BIT"},                    performBitState},
             {performBitState,                      hsm::Event{"START_MAIN_ACQ"},               mainAcqState},
             {performBitState,                      hsm::Event{"START_REDUNDANT_ACQ"},          redundantAcqState},
             {mainFaultManagementState,             hsm::Event{"RESTORE_MAIN_ACQ"},             mainAcqState},
             {mainAcqState,                         hsm::Event{"ABORT_MAIN_ACQ"},               mainFaultManagementState},
             {mainFaultManagementState,             hsm::Event{"RESTORE_REDUNDANT_ACQ"},        redundantAcqState},
             {redundantAcqState,                    hsm::Event{"ABORT_REDUNDANT_ACQ"},          mainFaultManagementState},
             {mainFaultManagementState,             hsm::Event{"CALL_ERROR"},                   mainErrorState},
    });

    applicationManager_ = make_unique<ApplicationManager>("ApplicationManager", transitionTable, idleState);
}

bool FeederScheduler::initialize()
{
    return applicationManager_->initialize();
}

void FeederScheduler::run()
{
    applicationManager_->startHSM();
    applicationManager_->startFeederSystem();
}
