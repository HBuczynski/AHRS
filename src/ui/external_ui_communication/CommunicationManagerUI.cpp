#include "CommunicationManagerUI.h"

#include <interfaces/communication_process_ui/CommunicationStatusNotification.h>
#include <interfaces/wireless_commands/InitConnectionCommand.h>

#include <interfaces/hm/HMInvalidConnectionNotification.h>

#include <config_reader/ConfigurationReader.h>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace hsm;
using namespace config;
using namespace utility;
using namespace communication;

CommunicationManagerUI::CommunicationManagerUI(UICommunicationMode mode, uint8_t processNumber, const string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState)
    : HSM(name, transitionTable, rootState),
      connectionCounter_(0),
      mode_(mode),
      processNumber_(processNumber),
      wirelessCommunicationParameters_(config::ConfigurationReader::getUIWirelessCommunication(UI_PARAMETERS_FILE_PATH)),
      connectionEstablishingInterrupt_("UICommunicationManager"),
      connectionEstablished_(false),
      logger_(Logger::getInstance())
{}

CommunicationManagerUI::~CommunicationManagerUI()
{}

bool CommunicationManagerUI::initializeServer()
{
    if(processNumber_ == FIRST_PROCESS)
    {
        server_ = make_unique<ServerUDP>(wirelessCommunicationParameters_.firstSourcePort, this);
        client_ = make_unique<ClientTCP>(wirelessCommunicationParameters_.firstDestinationPort, wirelessCommunicationParameters_.firstDestinationAddress, mode_);
        client_->registerCallbackToHMProc(hmCallback_);
    }
    else if(processNumber_ == SECOND_PROCESS)
    {
        client_ = make_unique<ClientTCP>(wirelessCommunicationParameters_.secondDestinationPort, wirelessCommunicationParameters_.secondDestinationAddress, mode_);
        server_ = make_unique<ServerUDP>(wirelessCommunicationParameters_.secondSourcePort, this);
        client_->registerCallbackToHMProc(hmCallback_);
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-ExtCOMM- CommunicationManagerUI:: Process - ") + to_string(mode_) +". Wrong process number";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    server_->startListening();
    launchTimer();

    if (logger_.isDebugEnable())
    {
        const std::string message = string("-ExtCOMM- CommunicationManagerUI:: Process - ") + to_string(mode_) + ". Server initialized correctly.";
        logger_.writeLog(LogType::DEBUG_LOG, message);
    }

    return true;
}

void CommunicationManagerUI::registerCallbackToMainProc(std::function<void(std::vector<uint8_t>&)> callback)
{
    mainProcCallback_ = callback;
}

void CommunicationManagerUI::registerCallbackToHM(std::function<void(std::vector<uint8_t>&)> callback)
{
    hmCallback_ = callback;
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

                auto notification = CommunicationStatusNotification(UIExternalComCode::INIT_CONNECTION, getUIMode());
                auto packet = notification.getFrameBytes();

                if(logger_.isDebugEnable())
                {
                    const string message = string("-ExtCOMM- CommunicationManagerUI:: Process - ") + to_string(mode_) +". Send to main: "
                            + notification.getName();
                    logger_.writeLog(LogType::DEBUG_LOG, message);
                }

                mainProcCallback_(packet);
            }
        }
    }
    else
    {
        connectionEstablishingInterrupt_.stop();
    }

    if (++connectionCounter_ > MAX_CONNECTION_NUMBER)
    {
        HMInvalidConnectionNotification command(processNumber_);
        auto packet = command.getFrameBytes();
        hmCallback_(packet);

        connectionCounter_ = 0;
    }
}

bool CommunicationManagerUI::connectToFeeder()
{
    unique_ptr<InitConnectionCommand> command;

    if(processNumber_ == config::FIRST_PROCESS)
    {
        command = make_unique<InitConnectionCommand>(wirelessCommunicationParameters_.firstSourcePort, wirelessCommunicationParameters_.firstSourceAddress);
    }
    else if(processNumber_ == config::SECOND_PROCESS)
    {
        command = make_unique<InitConnectionCommand>(wirelessCommunicationParameters_.secondSourcePort, wirelessCommunicationParameters_.secondSourceAddress);
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-ExtCOMM- CommunicationManagerUI:: Process - ") + to_string(mode_) +". Wrong process number";
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
            const string message = string("-ExtCOMM- CommunicationManagerUI:: Process - ") + to_string(mode_) +". Cannot connect to server.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}

bool CommunicationManagerUI::reconnect()
{
    return true;
}

void CommunicationManagerUI::sendCommands(unique_ptr<Command> command)
{
    client_->sendCommand(move(command));
}

UICommunicationMode CommunicationManagerUI::getUIMode() const
{
    return mode_;
}

void CommunicationManagerUI::setDBParameters(uint32_t hash, const std::string& name)
{
    server_->registerDbParameters(hash, name);
}

void CommunicationManagerUI::setMode(config::UICommunicationMode mode)
{
    mode_ = mode;

    client_->setMode(mode);
}
