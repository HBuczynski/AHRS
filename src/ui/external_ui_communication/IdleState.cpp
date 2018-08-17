#include <config_reader/ConfigurationReader.h>
#include "IdleState.h"
#include "ConnectedState.h"

#include "CommunicationManagerUI.h"

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

IdleState::IdleState()
        : AbstractState("IdleState", UIExternalStateCode::IDLE),
          uiCommunicationSystemParameters_(config::ConfigurationReader::getUICommunicationProcessSystemParameters(UI_COMMUNICATION_PROCESS_PARAMETERS_PATH)),
          logger_(Logger::getInstance())
{}

IdleState::~IdleState()
{}

void IdleState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("IdleState :: Change state on ConnectedState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    setState(&communicationManagerUI, new ConnectedState() );

    if(communicationManagerUI.getProcessNumber() == 1)
    {
        if(uiCommunicationSystemParameters_.firstProcess.mode == UICommunicationMode::MASTER)
        {
            communicationManagerUI.masterProcess();
        }
        else
        {
            communicationManagerUI.redundantProcess();
        }
    }
    else
    {
        if(uiCommunicationSystemParameters_.secondProcess.mode == UICommunicationMode::MASTER)
        {
            communicationManagerUI.masterProcess();
        }
        else
        {
            communicationManagerUI.redundantProcess();
        }
    }
}

void IdleState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void IdleState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void IdleState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void IdleState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}