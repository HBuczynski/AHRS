#include "HMManager.h"

#include <interfaces/hm/HMNotificationFactory.h>
#include <config_reader/ConfigurationReader.h>

using namespace hm;
using namespace std;
using namespace utility;
using namespace config;
using namespace communication;
using namespace boost::interprocess;

HMManager::HMManager()
    :  runHM_(false),
       logger_(Logger::getInstance())
{}

HMManager::~HMManager()
{}

bool HMManager::initialize(const string &name)
{
    bool isSuccess = true;

    if ((name != "FEEDER") || (name != "UI"))
        return false;

    if (name == "UI") {
        const auto msgProperties = ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str());
        isSuccess &= initializeHMQueue(msgProperties.mainProcessQueueName, msgProperties.messageQueueNumber, msgProperties.messageSize);
    } else if (name == "FEEDER"){
        const auto msgProperties = ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH.c_str());
        isSuccess &= initializeHMQueue(msgProperties.mainProcessQueueName, msgProperties.messageQueueNumber, msgProperties.messageSize);
    }

    runHM_ = isSuccess;

    return isSuccess;
}

bool HMManager::initializeMainQueue(string name, uint32_t size)
{
    try
    {
        mainMessageQueue_ = make_shared<MessageQueueWrapper>(name, size);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-HM- HMManager:: During openning main queue - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = "-HM- HMManager:: Main massage queue initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    return true;
}

bool HMManager::initializeHMQueue(string name, uint32_t queueNumber, uint32_t size)
{
    try
    {
        hmMessageQueue_ = make_unique<MessageQueueWrapper>(name, queueNumber, size);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-HM- HMManager:: During openning main queue - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = "-HM- HMManager:: Main massage queue initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

void HMManager::run()
{
    HMNotificationFactory notificationFactory;

    while (runHM_)
    {
        try
        {
            const auto packet = hmMessageQueue_->receive();

            auto notification = notificationFactory.createNotification(packet);

            notification->accept(*this);
        }
        catch(interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-HM- HMManager :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void HMManager::visit(const HMRegisterNotification& command)
{
    //TODO create main queue after registration

    //nodesContainer_.insert(command.getHMNode(),std::chrono::steady_clock::now());

    if(logger_.isInformationEnable())
    {
        const string message = string("-HM- HMManager:: Received - HMRegisterNotification");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void HMManager::visit(const HMHeartbeatNotification& command)
{


    if(logger_.isInformationEnable())
    {
        const string message = string("-HM- HMManager:: Received - HMHeartbeatNotification");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void HMManager::visit(const HMRegisterMainNotification& command)
{

    if(logger_.isInformationEnable())
    {
        const string message = string("-HM- HMManager:: Received - HMRegisterMainNotification");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
