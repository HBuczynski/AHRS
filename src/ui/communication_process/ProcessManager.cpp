#include "ProcessManager.h"
#include <common/InterprocessData.h>
#include <interfaces/wireless_commands/Command.h>

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
    initialize();
    performBIT();
}

ProcessManager::~ProcessManager()
{
    if(managementThread_.joinable())
    {
        managementThread_.join();
    }
}

void ProcessManager::initialize()
{
    openQueue();
    initializeWirelessCommunication();
}

void ProcessManager::openQueue()
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

void ProcessManager::initializeWirelessCommunication()
{
    //TODO: get data from config FIle

    CommunicationParameters parameters = {0};

    communicationManagerUI_ = make_unique<CommunicationManagerUI>(parameters);
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

    uint32_t priority = 0;
    message_queue::size_type receivedSize = 0;

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

            break;
        }

        rawData.resize(receivedSize);
        rawData.shrink_to_fit();

        handleMessage(rawData);
    }
}

void ProcessManager::handleMessage(const vector<uint8_t > &data)
{
    //TODO: check packet correctness: header, CRC, checksum

    const auto commandType = static_cast<FrameType>(data[1]);

    switch(commandType)
    {
        case WIRELESS_COMMAND :
        {
            communicationManagerUI_->sendCommands(move(wirelessCommandFactory_.createCommand(data)));
            break;
        }
        case UI_COMMAND :
        {
            unique_ptr<UICommand> uiCommand(move(uiCommandFactory_.createCommand(data)));
            uiCommand->accept(reinterpret_cast<UICommandVisitor& >(*this)); // check correctness of it
            break;
        }
        default:
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("ProcessManager -- STATUS: ") + to_string(status_)
                                       +string(". Received wrong frame type from message queue.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
}

void ProcessManager::performBIT()
{
    //TODO: check connection with feeder
}

void ProcessManager::changeMode(CommunicationProcessMode mode)
{
    status_ = mode;
}

void ProcessManager::visit(UIChangeModeCommand &command)
{
    const auto newMode = command.getMode();

    //TODO
}
