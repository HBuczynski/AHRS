#include "ClientTCP.h"

#include <iostream>

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

void ClientTCP::connectToServer()
{
    socket_ = make_unique<SendStreamTCP>(port_, address_);
    try
    {
        socket_->connectToServer();
    }
    catch (exception &e)
    {
        if(logger_.isErrorEnable())
        {
            const string message =
                    string("ClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                    string("-. Received exception: ") + e.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void ClientTCP::startCommandSending()
{
    executeCommandsFlag_ = true;
    queue<std::unique_ptr<Command>> emptyCommandQueue;
    queue<std::unique_ptr<Response>> emptyResponseQueue;

    // Clear elements in queue.
    commandQueue_.swap(emptyCommandQueue);
    responseQueue_.swap(emptyResponseQueue);

    // In case if the preious connection was finished and there is no certainty that previous thread was joined.
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

unique_ptr<Response> ClientTCP::getResponse()
{
    lock_guard<mutex> lock(responseQueueMutex_);

    auto response = move(responseQueue_.front());
    responseQueue_.pop();

    return response;
}

bool ClientTCP::isCommandQueueEmpty()
{
    lock_guard<mutex> lock(commandQueueMutex_);
    return commandQueue_.empty();
}

bool ClientTCP::isResponseQueueEmpty()
{
    lock_guard<mutex> lock(responseQueueMutex_);
    return responseQueue_.empty();
}

unique_ptr<Command> ClientTCP::getFromCommandQueue()
{
    lock_guard<mutex> lock(commandQueueMutex_);

    auto command = move(commandQueue_.front());
    commandQueue_.pop();

    return command;
}

void ClientTCP::insertToResponseQueue(unique_ptr<Response> response)
{
    lock_guard<mutex> lock(responseQueueMutex_);
    responseQueue_.push(move(response));
}

void ClientTCP::executeCommands()
{
    while (executeCommandsFlag_)
    {
        if(!isCommandQueueEmpty())
        {
            const auto command = getFromCommandQueue();
            const auto commandType = command->getFrameBytes()[COMMAND_TYPE_POSITION];
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
                        const string message = string("ClientTCP :: Client data: ") + address_ + string(" and port: ") +
                                               to_string(port_) + string(". Send command: ") +
                                               command->getName();
                        logger_.writeLog(LogType::INFORMATION_LOG, message);
                    }

                    const auto responseFrame = socket_->receivePacket();

                    unique_ptr<Response> response = responseFactory_.createCommand(responseFrame);
                    response->accept(responseHandler_);

                    insertToResponseQueue(move(response));

                    isSuccess = true;
                }
            }
            catch (exception &e)
            {
                catchExceptions(e.what(), isEndConnectionSent, commandSendingCounter);
            }
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
                string("ClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                string("-. Received exception: ") + exception;
        logger_.writeLog(LogType::ERROR_LOG, message);
    }

    // Command was not sent by 5 times, end connection
    if (commandSendingCounter == (COMMAND_SENDING_REPETITION - 1))
    {
        unique_ptr<Response> response = make_unique<AckResponse>(AckType::FAIL);
        insertToResponseQueue(move(response));

        if(logger_.isErrorEnable())
        {
            const string message =
                    string("ClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
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
        insertToResponseQueue(move(response));

        if(logger_.isWarningEnable())
        {
            const string message =
                    string("ClienTCP :: Client data: ") + address_ + string(" and port: ") + to_string(port_) +
                    string("-. Ending connection command was sent. Connection with server is closed.");
            logger_.writeLog(LogType::WARNING_LOG, message);
        }
        executeCommandsFlag_ = false;
        socket_.reset();
    }
}





