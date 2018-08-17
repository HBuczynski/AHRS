#include "ConnectedState.h"
#include "MasterState.h"
#include "RedundantState.h"
#include <config_reader/ConfigurationReader.h>

#include "CommunicationManagerUI.h"

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

ConnectedState::ConnectedState()
    : AbstractState("ConnectedState", UIExternalStateCode::CONNECTED),
      logger_(Logger::getInstance())
{}

ConnectedState::~ConnectedState()
{}

void ConnectedState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{

}

void ConnectedState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("ConnectedState :: Change state on RedundantState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    setState(&communicationManagerUI, new RedundantState);
}

void ConnectedState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("ConnectedState :: Change state on MasterState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    setState(&communicationManagerUI, new MasterState);
}

void ConnectedState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void ConnectedState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}
