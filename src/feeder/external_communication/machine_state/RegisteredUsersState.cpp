#include "RegisteredUsersState.h"
#include "ClientUDPManager.h"

#include "ResetState.h"
#include "ShutdownState.h"

using namespace std;
using namespace utility;
using namespace communication;

RegisteredUsersState::RegisteredUsersState()
    : AbstractState("RegisteredUsersState", FeederExternalStateCode::REGISTERED_USERS)
{ }

RegisteredUsersState::~RegisteredUsersState()
{ }

void RegisteredUsersState::acceptedUsers(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("RegisteredUsersState :: Cannot stay on user acceptance.");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void RegisteredUsersState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status)
{

}

void RegisteredUsersState::calibrationPassed(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("RegisteredUsersState :: Cannot change on CalibratedSuccessState.");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void RegisteredUsersState::calibrationFailed(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("RegisteredUsersState :: Cannot change on FailedCalibratedState.");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void RegisteredUsersState::startDataSending(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("RegisteredUsersState :: Cannot change on SendingState.");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void RegisteredUsersState::restartProcess(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new ResetState);

    if(logger_.isInformationEnable())
    {
        const string message = string("IdleState :: Change state on ResetState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void RegisteredUsersState::shutdownProcess(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new ShutdownState);

    if(logger_.isInformationEnable())
    {
        const string message = string("IdleState :: Change state on ShutdownState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}