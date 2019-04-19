#include "CommScheduler.h"

#include "machine_state/UIInitConnectionState.h"
#include "machine_state/UIReconnectedState.h"
#include "machine_state/UIRedundantState.h"
#include "machine_state/UIIdleCommState.h"
#include "machine_state/UIMasterState.h"
#include "machine_state/UIErrorState.h"

using namespace std;

CommScheduler::CommScheduler(uint8_t processNumber)
{
    create(processNumber);
}

void CommScheduler::create(uint8_t processNumber)
{
    auto initConnectionState = make_shared<UIInitConnectionState>("InitConnectionState");
    states_["InitConnectionState"] = initConnectionState;
    auto reconnectedState = make_shared<UIReconnectedState>("ReconnectedState");
    states_["ReconnectedState"] = reconnectedState;
    auto idleCommState = make_shared<UIIdleCommState>("IdleCommState");
    states_["IdleCommState"] = idleCommState;
    auto redundantState = make_shared<UIRedundantState>("RedundantState");
    states_["RedundantState"] = redundantState;
    auto masterState = make_shared<UIMasterState>("MasterState");
    states_["MasterState"] = masterState;
    auto errorState = make_shared<UIErrorState>("ErrorState");
    states_["ErrorState"] = errorState;

    /*Define transition table */
    hsm::TransitionTable transitionTable({
            {initConnectionState,           hsm::Event{"INIT_MASTER"},          masterState},
            {initConnectionState,           hsm::Event{"INIT_REDUNDANT"},       redundantState},
            {initConnectionState,           hsm::Event{"INIT_ERROR"},           errorState},
            {errorState,                    hsm::Event{"RECONNECTE"},           reconnectedState},
            {reconnectedState,              hsm::Event{"RECONNECT_MASTER"},     masterState},
            {reconnectedState,              hsm::Event{"RECONNECT_REDUNDANT"},  redundantState},
            {masterState,                   hsm::Event{"MASTER_ERROR"},         errorState},
            {redundantState,                hsm::Event{"REDUNDANT_ERROR"},      errorState},

    });

    procesManagerUI_ = make_shared<communication::ProcessManager>(processNumber, "CommunicationManagerUI", transitionTable, idleCommState);
}

bool CommScheduler::initialize()
{
    return procesManagerUI_->initialize();
}

void CommScheduler::run()
{
    procesManagerUI_->startCommunication();
}
