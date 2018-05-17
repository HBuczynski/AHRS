#include "ProcessManager.h"
#include <main_process/InterprocessData.h>
#include <protocol/Command.h>

using namespace std;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

ProcessManager::ProcessManager(std::string managementQueueName, std::string sharedMemoryName, CommunicationProcessMode status)
    : status_(status),
      runReceivingManagementCommandThread_(false),
      runSendingCommandThread_(false),
      managementQueueName_(managementQueueName),
      sharedMemoryName_(sharedMemoryName),
      logger_(Logger::getInstance())
{
    initialization();
    performBIT();
}

void ProcessManager::initialization()
{
    try
    {
        messageQueue_ = make_unique<message_queue>(open_only, managementQueueName_.c_str());
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("ProcessManager -- STATUS: ") + to_string(status_) +". During openning queue ::" + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

ProcessManager::~ProcessManager()
{
    if(managementThread_.joinable())
    {
        managementThread_.join();
    }
}

void ProcessManager::run()
{
    runReceivingManagementCommandThread_ = true;
    managementThread_ = thread(&ProcessManager::processReceivingManagementCommand, this);
}

void ProcessManager::stopRun()
{
    runReceivingManagementCommandThread_ = false;

    if(managementThread_.joinable())
    {
        managementThread_.join();
    }
}

void ProcessManager::processReceivingManagementCommand()
{
    vector<uint8_t> rawData;
    rawData.resize(MESSAGE_QUEUE_DATA_SIZE);

    uint32_t priority;
    message_queue::size_type receivedSize;

    while (runReceivingManagementCommandThread_)
    {
        try
        {
            messageQueue_->receive(rawData.data(), rawData.size(), receivedSize, priority);
        }
        catch(interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("ProcessManager -- STATUS: ") + to_string(status_) +". Receiving data ::" + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        rawData.resize(receivedSize);
        rawData.shrink_to_fit();

        //TODO
        // check packet correctness
        // header, CRC, checksum
        // find a command
    }
}

void ProcessManager::performBIT()
{

}

void ProcessManager::changeMode(CommunicationProcessMode mode)
{
    status_ = mode;
}
