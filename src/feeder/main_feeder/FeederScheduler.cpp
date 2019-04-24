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
    auto connectionState = make_shared<InitConnectionState>("ConnectionState", idleState);
    states_["ConnectionState"] = connectionState;


    /*Define transition table */
    hsm::TransitionTable transitionTable({
//            {connectionState,                   hsm::Event{"RECONNECT"},            reconnectedState},
//            {reconnectedState,                  hsm::Event{"REC_ERROR"},            errorState},
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
