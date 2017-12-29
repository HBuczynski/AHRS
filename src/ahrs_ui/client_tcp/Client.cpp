#include "Client.h"

using namespace std;
using namespace communication;

Client::Client(uint16_t portIn, string addressIn)
    : port_(portIn),
      address_(addressIn),
      executeCommandsFlag_(false)
{}

Client::~Client()
{
    stopCommandSending();
}

void Client::startCommandSending()
{
    socket_ = make_unique<SendStreamTCP>(port_, address_);

    executeCommandsFlag_ = true;
    executeCommandThread_ = thread(&Client::executeCommands, this);
}

void Client::stopCommandSending()
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

void Client::sendCommand(std::unique_ptr<Command> command, ResponseNotification *notification)
{
    unique_lock<mutex> lockGurad(conditionalVariableMutex_);
    insertToQueue(make_pair(move(command), notification));

    conditionVariable_.wait(lockGurad);
}

bool Client::isQueueEmpty()
{
    lock_guard<mutex> lock(commandQueueMutex_);
    return commandQueue_.empty();
}

CommandInQueue Client::getFromQueue()
{
    lock_guard<mutex> lock(commandQueueMutex_);

    auto commandPair = move(commandQueue_.front());
    commandQueue_.pop();

    return commandPair;
}

void Client::insertToQueue(CommandInQueue command)
{
    lock_guard<mutex> lock(commandQueueMutex_);
    commandQueue_.push(move(command));
}

void Client::executeCommands()
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

                    const auto responseFrame = socket_->receivePacket();

                    commandPair.second->received(responseFrame);

                    lock_guard<mutex> lock(conditionalVariableMutex_);
                    conditionVariable_.notify_one();

                    isSuccess = true;
                }
            }
            catch (exception &e)
            {
                // in case if command is not send
                // in case if response is not received
            }
        }
    }
}

