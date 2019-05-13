#include "ApplicationManager.h"

#include <machine_state/MainAcqState.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace main_process;
using namespace communication;
using namespace boost::interprocess;

extern char **environ;

ApplicationManager::ApplicationManager(const string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState)
    :   hsm::HSM(name, transitionTable, rootState),
        sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
        messageQueuesParameters_(ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH)),
        executableFilesNames_(ConfigurationReader::getFeederExecutableFiles(FEEDER_PARAMETERS_FILE_PATH)),
        runFeederSystem_(true),
        logger_(Logger::getInstance())
{
    externalVisitor_.registerApplicationManager(this);
}

ApplicationManager::~ApplicationManager()
{
    if(processingThread_.joinable())
    {
        processingThread_.join();
    }
}

bool ApplicationManager::initialize()
{
    bool isSuccess = true;

    isSuccess &= initializeMainQueue();
    isSuccess &= initializeExternalQueue();
    isSuccess &= initializeInternalQueue();

    isSuccess &= initializeExternalSharedMemory();
    isSuccess &= initializeInternalSharedMemory();

    isSuccess &= initializeFeederDB();

    isSuccess &= createExternalCommunicationProcess();
    isSuccess &= createInternalCommunicationProcess();

    return isSuccess;
}

bool ApplicationManager::initializeMainQueue()
{
    try
    {
        mainComMessageQueue = make_shared<MessageQueueWrapper>(messageQueuesParameters_.mainProcessQueueName,
                                                                messageQueuesParameters_.messageQueueNumber,
                                                                messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-MAIN- ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- ApplicationManager :: Main queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ApplicationManager::initializeExternalQueue()
{
    try
    {
        externalComMessageQueue = make_shared<MessageQueueWrapper>(messageQueuesParameters_.externalCommunicationQueueName,
                                                            messageQueuesParameters_.messageQueueNumber,
                                                            messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-MAIN- ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- ApplicationManager :: External queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ApplicationManager::initializeInternalQueue()
{
    try
    {
        internalComMessageQueue = make_shared<MessageQueueWrapper>(messageQueuesParameters_.internalCommunicationQueueName,
                                                                    messageQueuesParameters_.messageQueueNumber,
                                                                    messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-MAIN- ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- ApplicationManager :: Internal queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ApplicationManager::initializeFeederDB()
{
    bool isSuccess = true;

    const auto dbName = string("FeederDB_") + TimeManager::getTimeAndDate() + string(".db");

    dataContainer_.dbName = dbName;
    feederDb_ = make_shared<database::FeederDb>(dbName);

    isSuccess = isSuccess & feederDb_->openDb();
    isSuccess = isSuccess & feederDb_->createTable();

    auto state = getState("MainAcqState");
    isSuccess = isSuccess & static_pointer_cast<MainAcqState, hsm::State>(state)->initializeDb(dbName);

    if(isSuccess)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("-MAIN- UIApplicationManager:: Database has initialized correctly.");
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- UIApplicationManager:: Database has not initialized correctly - ");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        return false;
    }

    return isSuccess;
}

bool ApplicationManager::initializeExternalSharedMemory()
{
    try
    {
        externalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName, sharedMemoryParameters_.sharedMemorySize);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-MAIN- ApplicationManager:: External SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- ApplicationManager :: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ApplicationManager::initializeInternalSharedMemory()
{
    try
    {
        internalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.internalMemoryName, sharedMemoryParameters_.sharedMemorySize);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable()) {
            const std::string message = std::string("-MAIN- ApplicationManager:: Internal SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- ApplicationManager :: Internal shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ApplicationManager::createExternalCommunicationProcess()
{
    char *firstArg1 = const_cast<char*>(executableFilesNames_.externalCommunication.c_str());
    char *arguments[] = {firstArg1, NULL};

    int status;

    // This attribute is responsible for file descriptors.
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);

    status = posix_spawn(&externalProcess_, arguments[0], &action, NULL, arguments, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("-MAIN- ApplicationManager :: External process was initialized, process ID: ") + to_string(externalProcess_);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

        return true;
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- ApplicationManager :: External process was not initialized correctly, process ID: ") + to_string(externalProcess_);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }
}

bool ApplicationManager::createInternalCommunicationProcess()
{
    char *firstArg1 = const_cast<char*>(executableFilesNames_.internalCommunication.c_str());
    char *arguments[] = {firstArg1, NULL};

    int status;

    // This attribute is responsible for file descriptors.
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);

    status = posix_spawn(&internalProcess_, arguments[0], &action, NULL, arguments, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("-MAIN- ApplicationManager :: Internal process was initialized, process ID: ") + to_string(internalProcess_);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

        return true;
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- ApplicationManager :: Internal process was not initialized correctly, process ID: ") + to_string(internalProcess_);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }
}

void ApplicationManager::startFeederSystem()
{
    processingThread_ = thread(&ApplicationManager::runProcessing, this);
}

void ApplicationManager::stopFeederSystem()
{
    runFeederSystem_ = false;
}

void ApplicationManager::runProcessing()
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ApplicationManager :: Run processing.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    while(runFeederSystem_)
    {
        try
        {
            const auto packet = mainComMessageQueue->receive();
            handleCommand(packet);
        }
        catch(interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-MAIN- ApplicationManager :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void ApplicationManager::handleCommand(const std::vector<uint8_t>& packet)
{
    const auto interfaceType = static_cast<InterfaceType>(packet[Frame::INTERFACE_TYPE]);

    if(interfaceType == InterfaceType::COMMUNICATION_PROCESS_FEEDER)
    {
        const auto frameType = static_cast<FrameType>(packet[Frame::FRAME_TYPE]);

        if(frameType == FrameType::COMMAND)
        {
            const auto command = externalCommandFactory_.createCommand(packet);
            command->accept(externalVisitor_);
        }
        else if (frameType == FrameType::NOTIFICATION)
        {
            const auto notification = externalNotificationFactory_.createNotification(packet);
            notification->accept(externalVisitor_);
        }
        else
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-MAIN- ProcessManager :: Rceived wrong type of message");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
    else if (interfaceType == InterfaceType::ETHERNET_FEEDER)
    {
        //TODO
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- ProcessManager :: Rceived wrong type of message");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

FeederDataContainer &ApplicationManager::getFeederDataContainer()
{
    return dataContainer_;
}

void ApplicationManager::setPlaneName(const std::string& name) noexcept
{
    dataContainer_.planeName = name;
}

void ApplicationManager::setHash(uint32_t hash) noexcept
{
    feederDb_->insertHASH(hash);
}

void ApplicationManager::restartExternalProcess()
{

}

void ApplicationManager::restartInternalProcess()
{

}

void ApplicationManager::sendToExternalCommunicationProcess(std::vector<uint8_t> data)
{
    externalComMessageQueue->send(data);
}
