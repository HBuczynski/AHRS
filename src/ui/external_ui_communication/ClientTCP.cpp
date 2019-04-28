#include "ClientTCP.h"

#include <iostream>
#include <interfaces/wireless_responses/AckResponse.h>

using namespace std;
using namespace utility;
using namespace communication;

ClientTCP::ClientTCP(uint16_t portIn, string addressIn)
    : port_(portIn),
      address_(addressIn),
      executeCommandsFlag_(false),
      logger_(Logger::getInstance())
{}

ClientTCP::~ClientTCP()
{
    stopCommandSending();
}

bool ClientTCP::connectToServer()
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
                    string("-ExtCOMM- ClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                    string("-. Received exception: ") + e.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }
}

void ClientTCP::startCommandSending()
{
    executeCommandsFlag_ = true;
    queue<std::unique_ptr<Command>> emptyCommandQueue;

    // Clear elements in queue.
    commandQueue_.swap(emptyCommandQueue);

    // In case if the previous connection was finished and there is no certainty that previous thread was joined.
    if(executeCommandThread_.joinable())
    {
        executeCommandThread_.join();
    }

    executeCommandThread_ = thread(&ClientTCP::executeCommands, this);
}

void ClientTCP::stopCommandSending()
{
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

void ClientTCP::sendCommand(unique_ptr<Command> command)
{
    lock_guard<mutex> lock(commandQueueMutex_);
    commandQueue_.push(move(command));
}

bool ClientTCP::isCommandQueueEmpty()
{
    lock_guard<mutex> lock(commandQueueMutex_);
    return commandQueue_.empty();
}

unique_ptr<Command> ClientTCP::getFromCommandQueue()
{
    lock_guard<mutex> lock(commandQueueMutex_);

    auto command = move(commandQueue_.front());
    commandQueue_.pop();

    return command;
}

void ClientTCP::executeCommands()
{
    while (executeCommandsFlag_)
    {
        if(!isCommandQueueEmpty())
        {
            const auto command = getFromCommandQueue();
            const auto commandType = command->getFrameBytes()[Frame::COMMAND_TYPE_POSITION];
            bool isEndConnectionSent = false;

            if(commandType == END_CONNECTION)
            {
                isEndConnectionSent = true;
            }

            bool isSuccess = false;
            uint8_t commandSendingCounter;

            try
            {
                for(commandSendingCounter=0; commandSendingCounter < COMMAND_SENDING_REPETITION && !isSuccess; ++commandSendingCounter)
                {
                    socket_->sendData(command->getFrameBytes());


                    if(logger_.isInformationEnable())
                    {
                        const string message = string("-ExtCOMM- ClientTCP :: Client data: ") + address_ + string(" and port: ") +
                                               to_string(port_) + string(". Send command: ") +
                                               command->getName();
                        logger_.writeLog(LogType::INFORMATION_LOG, message);
                    }

                    const auto responseFrame = socket_->receivePacket();

                    unique_ptr<Response> response = responseFactory_.createCommand(responseFrame);
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

void ClientTCP::catchExceptions(string exception, bool isEndConnectionSent, uint8_t commandSendingCounter)
{
    // 1. Response command is not register in factory
    // 2. Command was not sent properly.
    // 3. Command was not receive properly.
    // 4. End connection command was sent.
    // Log error to file.

    if(logger_.isErrorEnable() && !isEndConnectionSent)
    {
        const string message =
                string("-ExtCOMM- ClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                string("-. Received exception: ") + exception;
        logger_.writeLog(LogType::ERROR_LOG, message);
    }

    // Command was not sent by 5 times, end connection
    if (commandSendingCounter == (COMMAND_SENDING_REPETITION - 1))
    {
        unique_ptr<Response> response = make_unique<AckResponse>(AckType::FAIL);
//        insertToResponseQueue(move(response));

        if(logger_.isErrorEnable())
        {
            const string message =
                    string("-ExtCOMM- ClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                    string("-. Sending command was repeated by 5 times, no response was received. Connection with server is closed.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        executeCommandsFlag_ = false;
        socket_.reset();
    }

    // End Connection was sent.
    if(isEndConnectionSent)
    {
        unique_ptr<Response> response = make_unique<AckResponse>(AckType::CONNECTION_ENDED);
//        insertToResponseQueue(move(response));

        if(logger_.isWarningEnable())
        {
            const string message =
                    string("-ExtCOMM- ClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                    string("-. Ending connection command was sent. Connection with server is closed.");
            logger_.writeLog(LogType::WARNING_LOG, message);
        }
        executeCommandsFlag_ = false;
        socket_.reset();
    }
}





