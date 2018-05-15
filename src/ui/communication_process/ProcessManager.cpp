#include "ProcessManager.h"

using namespace std;
using namespace communication;
using namespace boost::interprocess;

ProcessManager::ProcessManager(std::string managementQueueName, std::string sharedMemoryName, CommunicationProcessMode status)
    : status_(status),
      runReceivingManagementCommandThread_(false),
      runSendingCommandThread_(false),
      managementQueueName_(managementQueueName),
      sharedMemoryName_(sharedMemoryName)
{

}

ProcessManager::~ProcessManager()
{
    runReceivingManagementCommandThread_ = false;

    if(managementThread_.joinable())
    {
        managementThread_.join();
    }
}

void ProcessManager::run()
{
    runSendingCommandThread_ = true;
    runReceivingManagementCommandThread_ = true;

    managementThread_ = thread(&ProcessManager::processReceivingManagementCommand, this);

    processSendCommands();

    if(managementThread_.joinable())
    {
        managementThread_.join();
    }
}

void ProcessManager::stopRun()
{
    if(managementThread_.joinable())
    {
        managementThread_.join();
    }
}

CommunicationProcessMode ProcessManager::getMode() const
{
    return status_;
}

void ProcessManager::processReceivingManagementCommand()
{
    while (runReceivingManagementCommandThread_)
    {

    }
}

void ProcessManager::processSendCommands()
{
    if(status_ == CommunicationProcessMode::MAIN)
    {
        while (runSendingCommandThread_)
        {

        }
    }
}

void ProcessManager::performBIT()
{

}
