#include "ApplicationManager.h"

#include <machine_state/MainAcqState.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <utility/Utility.h>

#include <interfaces/hm/HMRegisterMainNotification.h>
#include <interfaces/hm/HMHeartbeatNotification.h>

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
        hmVisitor_(make_unique<HMFeederVisitor>(this)),
        runFeederSystem_(true),
        timerInterrupt_("MainFeeder"),
        logger_(Logger::getInstance())
{}

ApplicationManager::~ApplicationManager()
{
    if(processingThread_.joinable())
    {
        processingThread_.join();
    }

    timerInterrupt_.stop();
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

    initializeHMMessageQueue();
    initializeHM();

    externalVisitor_.registerApplicationManager(this);

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

bool ApplicationManager::initializeHMMessageQueue()
{
    try
    {
        hmMessageQueue_ = make_shared<MessageQueueWrapper>(messageQueuesParameters_.hmQueueName, messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- UIApplicationManager:: ") + messageQueuesParameters_.hmQueueName + (" queue has not been initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- UIApplicationManager:: Main message queue has been initialized correctly.");
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

bool ApplicationManager::initializeHM()
{
    if (!hmMessageQueue_)
        return true;

    HMRegisterMainNotification notification(HMNodes::MAIN_FEEDER, messageQueuesParameters_.mainProcessQueueName, messageQueuesParameters_.messageSize);

    auto packet = notification.getFrameBytes();
    hmMessageQueue_->send(packet);

    timerInterrupt_.startPeriodic(HM_INTERVAL_MS, this);

    return true;
}

void ApplicationManager::interruptNotification(timer_t timerID)
{
    HMHeartbeatNotification notification(HMNodes::MAIN_FEEDER);

    auto packet = notification.getFrameBytes();
    hmMessageQueue_->send(packet);
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

    runDbThread_ = true;
    dbThread_ = thread(&ApplicationManager::saveGeneralData2DB, this);
}

void ApplicationManager::stopFeederSystem()
{
    runFeederSystem_ = false;
    if(processingThread_.joinable())
        processingThread_.join();

    runDbThread_ = false;
    if(dbThread_.joinable())
        dbThread_.join();
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
    else if (interfaceType == InterfaceType::HM)
    {
        const auto frameType = static_cast<FrameType>(packet[Frame::FRAME_TYPE]);

        if(frameType == FrameType::COMMAND)
        {
            auto command = hmCommandFactory_.createCommand(packet);
            command->accept(*(hmVisitor_.get()));
        }
        else
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("UIApplicationManager :: Received wrong type of HM's message.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
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

void ApplicationManager::sendToInternalCommunicationProcess(std::vector<uint8_t> data)
{
    internalComMessageQueue->send(data);
}

void ApplicationManager::saveGeneralData2DB()
{
    FeederProperties data = {0};

    while (runDbThread_)
    {
        const auto cores = Utility::getCPU(400);

        data.bandwith = 2.4;
        data.mode = 24;
        data.power = 100;
        data.timestamp = TimeManager::getImeSinceEpoch();
        data.core1 = cores[0] * 100.0f;
        data.core2 = cores[1] * 100.0f;
        data.core3 = cores[2] * 100.0f;
        data.core4 = cores[3] * 100.0f;

        feederDb_->insertFeederProperties(data);

        this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}
