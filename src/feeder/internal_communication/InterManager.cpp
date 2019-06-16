#include "InterManager.h"

#include <interfaces/communication_process_ui/CommunicationStatusNotification.h>
#include <interfaces/wireless_commands/InitConnectionCommand.h>

#include <config_reader/ConfigurationReader.h>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

InterManager::InterManager()
    : internalCommunicationParameters_(config::ConfigurationReader::getFeederInternalWireless(FEEDER_PARAMETERS_FILE_PATH)),
      connectionEstablished_(false),
      logger_(Logger::getInstance())
{
    client_ = make_unique<InterClientTCP>(internalCommunicationParameters_.destinationPort, internalCommunicationParameters_.destinationAddress);
}

InterManager::~InterManager()
{}

void InterManager::launchTimer()
{
    connectionEstablishingInterrupt_.startPeriodic(5000, this);
}

void InterManager::interruptNotification(timer_t timerID)
{
    if(!connectionEstablished_)
    {
        if ( connectionEstablishingInterrupt_.getTimerID() == timerID )
        {
            if (connectToFeeder())
            {
                connectionEstablished_ = true;

                if(logger_.isInformationEnable())
                {
                    const string message = string("-INTCOM- InterManager:: Connection established.");
                    logger_.writeLog(LogType::INFORMATION_LOG, message);
                }
            }
        }
    }
    else
    {
        connectionEstablishingInterrupt_.stop();
    }
}

bool InterManager::connectToFeeder()
{
    auto command = make_unique<InitConnectionCommand>(internalCommunicationParameters_.sourcePort, internalCommunicationParameters_.sourceAddress);

    if(client_->connectToServer())
    {
        client_->startCommandSending();
        sendCommands(move(command));
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-INTCOM- InterManager:: Cannot connect to server.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        return false;
    }
    return true;
}

void InterManager::sendCommands(unique_ptr<Command> command)
{
    client_->sendCommand(move(command));
}
