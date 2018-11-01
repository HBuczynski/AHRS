#include "CommunicationManagerUI.h"
#include "ui/external_ui_communication/machine_state/IdleState.h"

#include <config_reader/ConfigurationReader.h>
#include <interfaces/wireless_commands/InitConnectionCommand.h>
#include <interfaces/wireless_commands/CollectDataCommand.h>
#include <interfaces/wireless_commands/EndConnectionCommand.h>
#include <iostream>

#include <thread>
#include <chrono>
#include <interfaces/wireless_commands/PerformBITsCommand.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

CommunicationManagerUI::CommunicationManagerUI(uint8_t processNumber)
    : currentState_(make_unique<IdleState>()),
      processNumber_(processNumber),
      wirelessCommunicationParameters_(config::ConfigurationReader::getUIWirelessCommunication(UI_PARAMETERS_FILE_PATH)),
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

    if (logger_.isInformationEnable())
    {
        const std::string message = string("CommunicationManagerUI:: Process - ") + to_string(processNumber_) + ". Server initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
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

    connectedToServer();

    return true;
}

void CommunicationManagerUI::sendCommands(unique_ptr<Command> command)
{
    client_->sendCommand(move(command));
}

const UIExternalStateCode& CommunicationManagerUI::getCurrentState() const
{
    return currentState_->getStateCode();
}

uint8_t CommunicationManagerUI::getProcessNumber() const
{
    return processNumber_;
}

void CommunicationManagerUI::setNewState(AbstractState *newState)
{
    if(newState != nullptr)
    {
        currentState_.reset(newState);
    }
    else
    {
        if(logger_.isWarningEnable())
        {
            const string message = string("CommunicationManagerUI :: Empty state has been forwarded to the state machine.");
            logger_.writeLog(LogType::WARNING_LOG, message);
        }
    }
}

void CommunicationManagerUI::connectedToServer()
{
    currentState_->connectedToServer(*this);
}

void CommunicationManagerUI::redundantProcess()
{
    currentState_->redundantProcess(*this);
}

void CommunicationManagerUI::masterProcess()
{
    currentState_->masterProcess(*this);
}

void CommunicationManagerUI::restartProcess()
{
    currentState_->restartProcess(*this);
}

void CommunicationManagerUI::shutdownProcess()
{
    currentState_->shutdownProcess(*this);
}


