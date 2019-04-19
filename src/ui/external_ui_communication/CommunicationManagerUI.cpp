#include "CommunicationManagerUI.h"

#include <interfaces/communication_process_ui/CommunicationStatusNotification.h>
#include <interfaces/wireless_commands/InitConnectionCommand.h>

#include <config_reader/ConfigurationReader.h>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace hsm;
using namespace config;
using namespace utility;
using namespace communication;

CommunicationManagerUI::CommunicationManagerUI(uint8_t processNumber, const string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState)
    : HSM(name, transitionTable, rootState),
      processNumber_(processNumber),
      wirelessCommunicationParameters_(config::ConfigurationReader::getUIWirelessCommunication(UI_PARAMETERS_FILE_PATH)),
      connectionEstablished_(false),
      logger_(Logger::getInstance())
{}

CommunicationManagerUI::~CommunicationManagerUI()
{}

bool CommunicationManagerUI::initializeServer()
{
    if(processNumber_ == 1)
    {
        server_ = make_unique<ServerUDP>(wirelessCommunicationParameters_.firstSourcePort);
        client_ = make_unique<ClientTCP>(wirelessCommunicationParameters_.firstDestinationPort, wirelessCommunicationParameters_.firstDestinationAddress);
    }
    else if(processNumber_ == 2)
    {
        client_ = make_unique<ClientTCP>(wirelessCommunicationParameters_.secondDestinationPort, wirelessCommunicationParameters_.secondDestinationAddress);
        server_ = make_unique<ServerUDP>(wirelessCommunicationParameters_.secondSourcePort);
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("CommunicationManagerUI:: Process - ") + to_string(processNumber_) +". Wrong process number";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    server_->startListening();
    launchTimer();

    if (logger_.isInformationEnable())
    {
        const std::string message = string("CommunicationManagerUI:: Process - ") + to_string(processNumber_) + ". Server initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

void CommunicationManagerUI::registerCallbackToMainProc(std::function<void(std::vector<uint8_t>&)> callback)
{
    mainProcCallback_ = callback;
}

void CommunicationManagerUI::launchTimer()
{
    connectionEstablishingInterrupt_.startPeriodic(5000, this);
}

void CommunicationManagerUI::interruptNotification(timer_t timerID)
{
    if(!connectionEstablished_)
    {
        if ( connectionEstablishingInterrupt_.getTimerID() == timerID )
        {
            if (connectToFeeder())
            {
                connectionEstablished_ = true;

                auto notification = CommunicationStatusNotification(UIExternalComCode::INIT_CONNECTION, getProcessNumber());
                auto packet = notification.getFrameBytes();
                mainProcCallback_(packet);
            }
        }
    }
    else
    {
        connectionEstablishingInterrupt_.stop();
    }
}

bool CommunicationManagerUI::connectToFeeder()
{
    unique_ptr<InitConnectionCommand> command;

    if(processNumber_ == 1)
    {
        command = make_unique<InitConnectionCommand>(wirelessCommunicationParameters_.firstSourcePort, wirelessCommunicationParameters_.firstSourceAddress);
    }
    else if(processNumber_ == 2)
    {
        command = make_unique<InitConnectionCommand>(wirelessCommunicationParameters_.secondSourcePort, wirelessCommunicationParameters_.secondSourceAddress);
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("CommunicationManagerUI:: Process - ") + to_string(processNumber_) +". Wrong process number";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if(client_->connectToServer())
    {
        client_->startCommandSending();
        sendCommands(move(command));
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("CommunicationManagerUI:: Process - ") + to_string(processNumber_) +". Cannot connect to server.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}

void CommunicationManagerUI::sendCommands(unique_ptr<Command> command)
{
    client_->sendCommand(move(command));
}

uint8_t CommunicationManagerUI::getProcessNumber() const
{
    return processNumber_;
}
