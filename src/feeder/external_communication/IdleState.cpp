#include "IdleState.h"
#include "ShutdownState.h"
#include "ResetState.h"
#include "RegisteredUsersState.h"

using namespace std;
using namespace utility;
using namespace communication;

IdleState::IdleState()
    : AbstractState("IdleState", StateCode::IDLE)
{ }

IdleState::~IdleState()
{ }

void IdleState::acceptedUsers(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new RegisteredUsersState);

    if(logger_.isInformationEnable())
    {
        const string message = string("IdleState :: Change state on RegisteredUsersState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void IdleState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("IdleState :: Cannot start calibration");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void IdleState::calibrationPassed(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("IdleState :: Cannot change state on calibration passed");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void IdleState::calibrationFailed(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("IdleState :: Cannot change state on calibration failed");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void IdleState::startDataSending(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("IdleState :: Cannot start calibration");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void IdleState::restartProcess(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new ResetState);

    if(logger_.isInformationEnable())
    {
        const string message = string("IdleState :: Change state on ResetState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void IdleState::shutdownProcess(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new ShutdownState);

    if(logger_.isInformationEnable())
    {
        const string message = string("IdleState :: Change state on ShutdownState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}