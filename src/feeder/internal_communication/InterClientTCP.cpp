#include "InterClientTCP.h"

#include <iostream>
#include <interfaces/ethernet_feeder/EthFeederResponse.h>
#include <interfaces/ethernet_feeder/EthAckFeederResponse.h>
#include <interfaces/ethernet_feeder/EthKeepAliveCommand.h>

using namespace std;
using namespace utility;
using namespace communication;

InterClientTCP::InterClientTCP(uint16_t portIn, string addressIn)
    : port_(portIn),
      address_(addressIn),
      executeCommandsFlag_(false),
      keepAliveTimer_("KeepAliveTimer"),
      logger_(Logger::getInstance())
{}

InterClientTCP::~InterClientTCP()
{
    if(logger_.isErrorEnable())
    {
        const string message =
                string("-InterClientTCP- ClientTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                string("-. Stopped Client Thread.");
        logger_.writeLog(LogType::ERROR_LOG, message);
    }

    stopCommandSending();
}

bool InterClientTCP::connectToServer()
{
    socket_ = make_unique<SendStreamTCP>(port_, address_);
    try
    {
        socket_->connectToServer();
        socket_->setTimeout();
        return true;
    }
    catch (exception &e)
    {
        if(logger_.isErrorEnable())
        {
            const string message =
                    string("-INTCOM- InterClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                    string("-. Received exception: ") + e.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }
}

void InterClientTCP::setConnectionCallback(std::function<void()> launchConnectionCallback)
{
    launchConnectionCallback_ = launchConnectionCallback;
}

void InterClientTCP::startCommandSending()
{
    executeCommandsFlag_ = true;
    queue<std::unique_ptr<EthFeederCommand>> emptyCommandQueue;

    // Clear elements in queue.
    commandQueue_.swap(emptyCommandQueue);

    // In case if the previous connection was finished and there is no certainty that previous thread was joined.
    if(executeCommandThread_.joinable())
    {
        executeCommandThread_.join();
    }

    keepAliveTimer_.stop();
    keepAliveTimer_.startPeriodic(KEEP_ALIVE_INTERVAL_MS, this);

    executeCommandThread_ = thread(&InterClientTCP::executeCommands, this);
}

void InterClientTCP::stopCommandSending()
{
    keepAliveTimer_.stop();

    if(executeCommandsFlag_)
    {
        executeCommandsFlag_ = false;

        if( socket_.get() != nullptr)
        {
            socket_.reset();
        };

        if(executeCommandThread_.joinable())
        {
            executeCommandThread_.join();
        }
    }
}

void InterClientTCP::sendCommand(unique_ptr<EthFeederCommand> command)
{
    lock_guard<mutex> lock(commandQueueMutex_);
    commandQueue_.push(move(command));
}

bool InterClientTCP::isCommandQueueEmpty()
{
    lock_guard<mutex> lock(commandQueueMutex_);
    return commandQueue_.empty();
}

unique_ptr<EthFeederCommand> InterClientTCP::getFromCommandQueue()
{
    lock_guard<mutex> lock(commandQueueMutex_);

    auto command = move(commandQueue_.front());
    commandQueue_.pop();

    return command;
}

void InterClientTCP::executeCommands()
{
    while (executeCommandsFlag_)
    {
        if(!isCommandQueueEmpty())
        {
            const auto command = getFromCommandQueue();
            bool isEndConnectionSent = false;


            bool isSuccess = false;
            uint8_t commandSendingCounter;

            try
            {
                for(commandSendingCounter=0; commandSendingCounter < COMMAND_SENDING_REPETITION && !isSuccess; ++commandSendingCounter)
                {
                    socket_->sendData(command->getFrameBytes());


                    if(logger_.isInformationEnable())
                    {
                        const string message = string("-INTCOMM- InterClientTCP :: Client data: ") + address_ + string(" and port: ") +
                                               to_string(port_) + string(". Send command: ") +
                                               command->getName();
                        logger_.writeLog(LogType::INFORMATION_LOG, message);
                    }

                    const auto responseFrame = socket_->receivePacket();

                    unique_ptr<EthFeederResponse> response = responseFactory_.createCommand(responseFrame);
                    response->accept(responseHandler_);

                    isSuccess = true;
                }
            }
            catch (exception &e)
            {
                cout << "In exception" << endl;
                catchExceptions(e.what(), isEndConnectionSent, commandSendingCounter);
            }
            this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }
}

void InterClientTCP::catchExceptions(string exception, bool isEndConnectionSent, uint8_t commandSendingCounter)
{
    // 1. Response command is not register in factory
    // 2. Command was not sent properly.
    // 3. Command was not receive properly.
    // 4. End connection command was sent.
    // Log error to file.

    if(!isEndConnectionSent)
    {
        const string message =
                string("-INTCOM- InterClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                string("-. Received exception: ") + exception;
        logger_.writeLog(LogType::ERROR_LOG, message);

        executeCommandsFlag_ = false;
        keepAliveTimer_.stop();
        socket_.reset();

        launchConnectionCallback_();
    }

    // Command was not sent by 5 times, end connection
    if (commandSendingCounter == (COMMAND_SENDING_REPETITION - 1))
    {
        unique_ptr<EthFeederResponse> response = make_unique<EthAckFeederResponse>();
//        insertToResponseQueue(move(response));

        if(logger_.isErrorEnable())
        {
            const string message =
                    string("-INTCOM- InterClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                    string("-. Sending command was repeated by 5 times, no response was received. Connection with server is closed.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        executeCommandsFlag_ = false;
        socket_.reset();
    }

    // End Connection was sent.
    if(isEndConnectionSent)
    {
        unique_ptr<EthFeederResponse> response = make_unique<EthAckFeederResponse>();
        if(logger_.isWarningEnable())
        {
            const string message =
                    string("-INTCOM- InterClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                    string("-. Ending connection command was sent. Connection with server is closed.");
            logger_.writeLog(LogType::WARNING_LOG, message);
        }
        executeCommandsFlag_ = false;
        socket_.reset();
    }
}

void InterClientTCP::interruptNotification(timer_t timerID)
{
    auto keepAliveCommand= make_unique<EthKeepAliveCommand>();
    sendCommand(move(keepAliveCommand));
}




