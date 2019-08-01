#include "HMManager.h"

#include <iomanip>
#include <ctime>
#include <chrono>

#include <interfaces/hm/HMErrorCommand.h>
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
       timerInterrupt_("HM"),
       logger_(Logger::getInstance())
{}

HMManager::~HMManager()
{
    timerInterrupt_.stop();
}

bool HMManager::initialize(const string &name)
{
    bool isSuccess = true;

    if ((name != "FEEDER") && (name != "UI"))
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-HM- HMManager:: Wrong arg - ") + name;
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (name == "UI") {
        const auto msgProperties = ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str());
        isSuccess &= initializeHMQueue(msgProperties.hmQueueName, msgProperties.messageQueueNumber, msgProperties.messageSize);

        if (logger_.isInformationEnable())
        {
            const std::string message = "-HM- HMManager:: " + msgProperties.hmQueueName + " massage queue initialized correctly.";
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

    } else if (name == "FEEDER"){
        const auto msgProperties = ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH.c_str());
        isSuccess &= initializeHMQueue(msgProperties.hmQueueName, msgProperties.messageQueueNumber, msgProperties.messageSize);

        if (logger_.isInformationEnable())
        {
            const std::string message = "-HM- HMManager:: " + msgProperties.hmQueueName + " massage queue initialized correctly.";
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }

    runHM_ = isSuccess;

    if (isSuccess)
         timerInterrupt_.startPeriodic(HM_THRESHOLD_MS, this);

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

            if (!packet.empty())
            {
                auto notification = notificationFactory.createNotification(packet);
                notification->accept(*this);
            }
        }
        catch(interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-HM- HMManager :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void HMManager::interruptNotification(timer_t timerID)
{
    TimePoint currentTime = std::chrono::steady_clock::now();

    {
        lock_guard<mutex> lock(containerMutex_);
        for(auto &node : nodesContainer_)
        {
            auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - node.second);

            if (delay.count() > 1.1 * HM_THRESHOLD_MS)
            {
                string temp = "";
                HMErrorCommand command(node.first, HMErrorType::OUT_HEARTBEAT, config::UICommunicationMode::MASTER, temp);
                auto packet = command.getFrameBytes();

                mainMessageQueue_->send(packet);

                if (logger_.isErrorEnable())
                {
                    const std::string message = "-HM- HMManager:: Error interrupt.";
                    logger_.writeLog(LogType::ERROR_LOG, message);
                }
            }
        }
    }
}

void HMManager::visit(const HMRegisterNotification& command)
{
    TimePoint time = std::chrono::steady_clock::now();
    HMNodes node = command.getHMNode();
    {
        lock_guard<mutex> lock(containerMutex_);
        nodesContainer_.insert({node, time});
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("-HM- HMManager:: Received - HMRegisterNotification, node: ") + to_string( static_cast<int>(node));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void HMManager::visit(const HMHeartbeatNotification& command)
{
    {
        lock_guard<mutex> lock(containerMutex_);
        auto iter = nodesContainer_.find(command.getHMNode());

        if ( iter != nodesContainer_.cend())
            nodesContainer_[command.getHMNode()] = std::chrono::steady_clock::now();
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("-HM- HMManager:: Received - HMHeartbeatNotification, node: ") + to_string( static_cast<int>(command.getHMNode()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void HMManager::visit(const HMRegisterMainNotification& command)
{
    TimePoint time = std::chrono::steady_clock::now();
    HMNodes node = command.getHMNode();

    {
        lock_guard<mutex> lock(containerMutex_);
        nodesContainer_.insert({node, time});
    }

    initializeMainQueue(command.getQueueName(), command.getQueueSize());

    if(logger_.isInformationEnable())
    {
        const string message = string("-HM- HMManager:: Received - HMRegisterMainNotification, node: ") + to_string( static_cast<int>(command.getHMNode()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void HMManager::visit(const HMErrorNotification& command)
{
    string temp ="";
    HMErrorCommand hmCommand(command.getHMNode(), command.getHMError(), command.getMode(), temp);
    auto packet = hmCommand.getFrameBytes();
    mainMessageQueue_->send(packet);

    if(logger_.isInformationEnable())
    {
        const string message = string("-HM- HMManager:: Received - HMErrorNotification");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void HMManager::visit(const communication::HMRemoveNodeNotification& command)
{
    HMNodes node = command.getHMNode();
    {
        lock_guard<mutex> lock(containerMutex_);
        auto iter = nodesContainer_.find(node);
        if (iter != nodesContainer_.end())
            nodesContainer_.erase(iter);
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("-HM- HMManager:: Received - HMRemoveNodeNotification, node: ") + to_string( static_cast<int>(node));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
