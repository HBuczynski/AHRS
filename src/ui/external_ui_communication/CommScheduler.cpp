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
            make_tuple(initConnectionState,           hsm::Event{"INIT_MASTER"},          masterState),
            make_tuple(initConnectionState,           hsm::Event{"INIT_REDUNDANT"},       redundantState),
            make_tuple(initConnectionState,           hsm::Event{"INIT_ERROR"},           errorState),
            make_tuple(errorState,                    hsm::Event{"RECONNECTE"},           reconnectedState),
            make_tuple(reconnectedState,              hsm::Event{"RECONNECT_MASTER"},     masterState),
            make_tuple(reconnectedState,              hsm::Event{"RECONNECT_REDUNDANT"},  redundantState),
            make_tuple(masterState,                   hsm::Event{"MASTER_ERROR"},         errorState),
            make_tuple(redundantState,                hsm::Event{"REDUNDANT_ERROR"},      errorState),
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
