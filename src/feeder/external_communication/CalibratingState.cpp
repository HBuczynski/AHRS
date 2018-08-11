#include "CalibratingState.h"

#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>

#include "RedundantSendingState.h"
#include "MasterSendingState.h"
#include "CalibratedFailedState.h"
#include "CalibratedSuccessState.h"
#include "ResetState.h"
#include "ShutdownState.h"

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

CalibratingState::CalibratingState()
        : AbstractState("CalibratingState", StateCode::CALIBRATING),
          messageQueuesParameters_(ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH))
{
    initializeMessageQueue();
}

CalibratingState::~CalibratingState()
{ }

void CalibratingState::initializeMessageQueue()
{
    try
    {
        mainMessageQueue = make_shared<message_queue>(open_only, messageQueuesParameters_.mainProcessQueueName.c_str());
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("CalibratingState: Interprocess communication :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void CalibratingState::acceptedUsers(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("CalibratingState :: Cannot change on RegisteredUserState.");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void CalibratingState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status)
{
    setState(&clientUDPManager, new CalibratingState);

    try
    {
        //TODO: create interprocess command
        //mainMessageQueue
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable()) {
            const string message = string("RegisteredUsersState :: Cannot send message to main process, error: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("RegisteredUsersState :: Change state on RegisteredUsersState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    if(logger_.isWarningEnable())
    {
        const string message = string("CalibratingState :: Calibration command has been sent again to the main procecss.");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void CalibratingState::calibrationPassed(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new CalibratedSuccessState());

    if(logger_.isInformationEnable())
    {
        const string message = string("CalibratingState :: Change state on CalibratedSuccessState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CalibratingState::calibrationFailed(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new CalibratedFailedState());

    if(logger_.isInformationEnable())
    {
        const string message = string("CalibratingState :: Change state on CalibratedFailedState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CalibratingState::startDataSending(ClientUDPManager &clientUDPManager)
{
    if(logger_.isWarningEnable())
    {
        const string message = string("CalibratingState :: Cannot change on DataSendingMode.");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }
}

void CalibratingState::restartProcess(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new ResetState);

    if(logger_.isInformationEnable())
    {
        const string message = string("CalibratingState :: Change state on ResetState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CalibratingState::shutdownProcess(ClientUDPManager &clientUDPManager)
{
    setState(&clientUDPManager, new ShutdownState);

    if(logger_.isInformationEnable())
    {
        const string message = string("CalibratingState :: Change state on ShutdownState");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}


