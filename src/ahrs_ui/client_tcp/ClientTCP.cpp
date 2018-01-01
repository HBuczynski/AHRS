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
    if(executeCommandThread_.joinable())
    {
        executeCommandThread_.join();
    }
}

void ClientTCP::connectToServer()
{
    socket_ = make_unique<SendStreamTCP>(port_, address_);
    socket_->connectToServer();
    // to do: try catch
}

void ClientTCP::startCommandSending()
{
    executeCommandsFlag_ = true;
    executeCommandThread_ = thread(&ClientTCP::executeCommands, this);
}

void ClientTCP::stopCommandSending()
{
    if(executeCommandsFlag_)
    {
        executeCommandsFlag_ = false;

        socket_.reset();

        if(executeCommandThread_.joinable())
        {
            executeCommandThread_.join();
        }
    }
}

void ClientTCP::sendCommand(std::unique_ptr<Command> command, ResponseNotification *notification)
{
    unique_lock<mutex> lockGurad(conditionalVariableMutex_);
    insertToQueue(make_pair(move(command), notification));

    conditionVariable_.wait(lockGurad);
}

bool ClientTCP::isQueueEmpty()
{
    lock_guard<mutex> lock(commandQueueMutex_);
    return commandQueue_.empty();
}

CommandInQueue ClientTCP::getFromQueue()
{
    lock_guard<mutex> lock(commandQueueMutex_);

    auto commandPair = move(commandQueue_.front());
    commandQueue_.pop();

    return commandPair;
}

void ClientTCP::insertToQueue(CommandInQueue command)
{
    lock_guard<mutex> lock(commandQueueMutex_);
    commandQueue_.push(move(command));
}

void ClientTCP::executeCommands()
{
    while (executeCommandsFlag_)
    {
        if(!isQueueEmpty())
        {
            const auto commandPair = getFromQueue();

            bool isSuccess = false;

            try
            {
                for(uint8_t i=0; i < COMMAND_SENDING_REPETITION && !isSuccess; ++i)
                {
                    socket_->sendData(commandPair.first->getFrameBytes());

                    string message = string("ClientTCP :: Client data: ") + address_ + string(" and port: ")+ to_string(port_) + string(". Send command: ") + commandPair.first->getName();
                    logger_.writeLog(LogType::INFORMATION_LOG, message);

                    const auto responseFrame = socket_->receivePacket();

                    const auto response = responseFactory_.createCommand(responseFrame);
                    response->accept(responseHandler_);

                    commandPair.second->received(responseFrame);

                    lock_guard<mutex> lock(conditionalVariableMutex_);
                    conditionVariable_.notify_one();

                    isSuccess = true;
                }
            }
            catch (exception &e)
            {
                string message = string("ClienTCP :: Client data: ") + address_ + string(" and port: ")+ to_string(port_) + string("-. Received exception: ") + e.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
                // in case if command is not send
                // in case if response is not received
                // co zrobic gdy wyslamy end connection
            }
        }
    }
}

