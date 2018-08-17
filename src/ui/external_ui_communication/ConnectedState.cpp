#include "ConnectedState.h"
#include "MasterState.h"
#include "RedundantState.h"
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

ConnectedState::ConnectedState()
    : AbstractState("ConnectedState", UIExternalStateCode::CONNECTED)
{}

ConnectedState::~ConnectedState()
{}

void ConnectedState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{

}

void ConnectedState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{
    setState(&communicationManagerUI, new RedundantState);

    if(logger_.isInformationEnable())
    {
        const string message = string("ConnectedState :: Change state on RedundantState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ConnectedState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{
    setState(&communicationManagerUI, new MasterState);

    if(logger_.isInformationEnable())
    {
        const string message = string("ConnectedState :: Change state on RedundantState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ConnectedState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void ConnectedState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}
