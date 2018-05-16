#include <unistd.h>
#include "Scheduler.h"
#include "InterprocessData.h"

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

        //Initialize Message Queue for management main process.
        message_queue::remove(MAIN_PROCESS_QUEUE_NAME.c_str());
        managementMessageQueue_ = make_unique<message_queue>(create_only, MAIN_PROCESS_QUEUE_NAME.c_str(),
                                                             MESSAGE_QUEUE_NUMBER, MESSAGE_QUEUE_DATA_SIZE);
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