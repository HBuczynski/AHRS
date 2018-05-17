#include <unistd.h>
#include "Scheduler.h"
#include <common/InterprocessData.h>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

using namespace std;
using namespace utility;
using namespace main_process;
using namespace communication;
using namespace boost::interprocess;

Scheduler::Scheduler()
    : runMainProcess_(false),
      previousState_(ProcessStates::START),
      state_(ProcessStates::START),
      logger_(Logger::getInstance())
{}

Scheduler::~Scheduler()
{
    // Removing message queues.
    message_queue::remove(RECEIVING_QUEUE_NAME_FIRST_PROC.c_str());
    message_queue::remove(RECEIVING_QUEUE_NAME_SECOND_PROC.c_str());

    // Removing shared memory.
    named_mutex::remove(SHARED_MEMORY_MUTEX_NAME.c_str());
    shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
}
// wzorzecz STATE
void Scheduler::run()
{
    runMainProcess_ = true;

    /*while(runMainProcess_)
    {
        switch(state_)
        {
            case START :
            {
                initialization();
                break;
            }
            case INITIALIZATION :
            {
                plainConfirmation();
                break;
            }
            case PLANE_CONFIRMATION:
            {
                magnetometerCalibration();
                break;
            }
            case DATA_ACQUSITION:
            {
                dataAcquisition();
                break;
            }
            case ERROR:
            {
                if(logger_.isErrorEnable())
                {
                    const string message = string("MainProcessScheduler :: Failure after state: ") + to_string(previousState_);
                    logger_.writeLog(LogType::ERROR_LOG, message);
                }
                termination();
                break;
            }
        }
    }*/
}

void Scheduler::stopRun()
{
    runMainProcess_ = false;
}

void Scheduler::initialization()
{
    for(uint8_t i=0; i < FAILURE_NUMBER; ++i)
    {
        try
        {
            initializeSwitches();
            initializeMessageQueues();
            initializeSharedMemory();
            initializeCommunicationProcesses();
            initializeGUI();

            previousState_ = ProcessStates::START;
            state_ = ProcessStates::INITIALIZATION;
            return;
        }
        catch (exception &e)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("MainProcessScheduler :: ") + e.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }

    previousState_ = ProcessStates::START;
    state_= ProcessStates::ERROR;
}

void Scheduler::initializeSwitches()
{
    SwitchesFactory switchesFactory;

    switches_ = switchesFactory.getConnectedSwitches();

    for(auto &singleSwitch : switches_)
    {
        singleSwitch->initializeCallbacks( bind(&Scheduler::interruptSwitchPressed, this, placeholders::_1),
                                           bind(&Scheduler::interruptSwitchError, this, placeholders::_1));
    }
}

void Scheduler::initializeMessageQueues()
{
    // During initialization process, the first process is always MAIN process.
    try {
        //Initialize Message Queue for first communication process.
        message_queue::remove(RECEIVING_QUEUE_NAME_FIRST_PROC.c_str());
        communicationQueues_[CommunicationProcessMode::MAIN] = make_shared<message_queue>(create_only,
                                                                                          RECEIVING_QUEUE_NAME_FIRST_PROC.c_str(),
                                                                                          MESSAGE_QUEUE_NUMBER,
                                                                                          MESSAGE_QUEUE_DATA_SIZE);

        //Initialize Message Queue for second communication process.
        message_queue::remove(RECEIVING_QUEUE_NAME_SECOND_PROC.c_str());
        communicationQueues_[CommunicationProcessMode::REDUNDANT] = make_shared<message_queue>(create_only,
                                                                                               RECEIVING_QUEUE_NAME_SECOND_PROC.c_str(),
                                                                                               MESSAGE_QUEUE_NUMBER,
                                                                                               MESSAGE_QUEUE_DATA_SIZE);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("MainProcessScheduler :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void Scheduler::initializeSharedMemory()
{
    try
    {
        // Creating shared memory's mutex.
        named_mutex::remove(SHARED_MEMORY_MUTEX_NAME.c_str());
        sharedMemoryMutex_ = make_unique<named_mutex>(create_only, SHARED_MEMORY_MUTEX_NAME.c_str());

        // Creating shared memory.
        shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
        sharedMemory_ = make_unique<shared_memory_object>(create_only, SHARED_MEMORY_NAME.c_str(), read_write);

        // Resize shared memory.
        sharedMemory_->truncate(SHARED_MEMORY_SIZE);
        mappedMemoryRegion_ = make_unique<mapped_region>(*sharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("MainProcessScheduler :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void Scheduler::initializeCommunicationProcesses()
{
    processesHandler.initializeProcesses();
}

void Scheduler::initializeGUI()
{
    //TODO
    // send information to gui about progress
}

void Scheduler::plainConfirmation()
{
    //TODO
    state_ = ProcessStates::ERROR;
}

void Scheduler::magnetometerCalibration()
{
    //TODO
    state_ = ProcessStates::ERROR;
}

void Scheduler::dataAcquisition()
{
    while(state_ == ProcessStates::DATA_ACQUSITION)
    {
        //TODO
    }
}

void Scheduler::interruptSwitchPressed(peripherals::SwitchesCode switchCode)
{
    switch (switchCode)
    {
        case peripherals::SwitchesCode::BOTTOM_SWITCH :
        {
            break;
        }
        case peripherals::SwitchesCode::UP_SWITCH :
        {
            break;
        }
        case peripherals::SwitchesCode::OK_SWITCH :
        {

            break;
        }
        case peripherals::SwitchesCode::CANCEL_SWITCH:
        {

            break;
        }
    }
}

void Scheduler::interruptSwitchError(peripherals::SwitchesCode switchCode)
{
    switch (switchCode)
    {
        case peripherals::SwitchesCode::BOTTOM_SWITCH :
        {
            break;
        }
        case peripherals::SwitchesCode::UP_SWITCH :
        {
            break;
        }
        case peripherals::SwitchesCode::OK_SWITCH :
        {

            break;
        }
        case peripherals::SwitchesCode::CANCEL_SWITCH:
        {

            break;
        }
    }
}

void Scheduler::sendMessageQueue(const vector<uint8_t> &payload, CommunicationProcessMode process)
{
    auto messageQueue = communicationQueues_.find(process);

    if(messageQueue != communicationQueues_.end())
    {
        try
        {
            messageQueue->second->send(payload.data(), payload.size(), 0);
        }
        catch(interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("MainProcessScheduler :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("MainProcessScheduler :: ") + string("Inavlid communication process code.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void Scheduler::termination()
{

}