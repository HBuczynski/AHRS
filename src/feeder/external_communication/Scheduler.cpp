#include "Scheduler.h"

#include "machine_state/ErrorState.h"
#include "machine_state/IdleState.h"
#include "machine_state/InitConnectionState.h"
#include "machine_state/ReconnectedState.h"

using namespace std;
using namespace communication;

Scheduler::Scheduler()
{
    create();
}

void Scheduler::create()
{
    auto idleState = make_shared<IdleState>("Idle");
    states_["Idle"] = idleState;
    auto connectionState = make_shared<InitConnectionState>("ConnectionState", idleState);
    states_["ConnectionState"] = connectionState;
    auto errorState = make_shared<ErrorState>("ErrorState", idleState);
    states_["ErrorState"] = errorState;
    auto reconnectedState = make_shared<ReconnectedState>("ReconnectedState", idleState);
    states_["ReconnectedState"] = reconnectedState;

    /*Define transition table */
    hsm::TransitionTable transitionTable({
            {connectionState,                   hsm::Event{"RECONNECT"},            reconnectedState},
            {reconnectedState,                  hsm::Event{"REC_ERROR"},            errorState},
    });

    processManager_ = make_unique<ProcessManager>("ProcessManager", transitionTable, idleState);
}

bool Scheduler::initialize()
{
    return processManager_->initialize();
}

void Scheduler::run()
{
    processManager_->startHSM();
    processManager_->start();
}


