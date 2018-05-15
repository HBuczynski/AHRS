#include <unistd.h>
#include "Scheduler.h"
#include <sys/wait.h>

using namespace std;
using namespace utility;
using namespace main_process;

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

    while(runMainProcess_)
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
    }
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
            initializeGUI();
            initializeSwitches();
            initializeMessageQueues();
            initializeSharedMemory();
            initializeCommunicationProcesses();

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

void Scheduler::initializeCommunicationProcesses()
{
    processesHandler.initializeProcesses();
}

void Scheduler::plainConfirmation()
{

    state_ = ProcessStates::ERROR;
}

void Scheduler::magnetometerCalibration()
{
    state_ = ProcessStates::ERROR;
}

void Scheduler::dataAcquisition()
{
    while(state_ == ProcessStates::DATA_ACQUSITION)
    {
        //TODO
    }
}


void Scheduler::initializeGUI()
{
    //TODO

    // send information to gui about progress
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

    // send information to gui about progress
}

void Scheduler::initializeMessageQueues()
{

}

void Scheduler::initializeSharedMemory()
{

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

void Scheduler::termination()
{

}