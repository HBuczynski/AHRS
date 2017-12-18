#include "ClientThreadTCP.h"

#include <waic_protocol/Command.h>

using namespace std;
using namespace communication;

ClientThreadTCP::ClientThreadTCP(unique_ptr<SendStreamTCP> socket, CallbackFunctions callbackFunctions)
    : socket_(std::move(socket)),
      callbackFunctions_(callbackFunctions),
      runListenThread_(false)
{
    initializeCommandHandler();
}

ClientThreadTCP::~ClientThreadTCP()
{
    if(listenThread_.joinable())
    {
        listenThread_.join();
    }
}

void ClientThreadTCP::initializeCommandHandler()
{
    commandHandler_.initializeCallbackFunction(callbackFunctions_);
    commandHandler_.initializeCurrentClient(this);
}

void ClientThreadTCP::setID(uint32_t id)
{
    id_ = id;
}

uint32_t ClientThreadTCP::getID()
{
    return id_;
}

void ClientThreadTCP::startListen()
{
    runListenThread_ = true;
    listenThread_ = thread(&ClientThreadTCP::runListen, this);
}

void ClientThreadTCP::stopListen()
{
    socket_.reset();
    runListenThread_ = false;
}

void ClientThreadTCP::runListen()
{
    while(runListenThread_)
    {
        try
        {
            auto frame = socket_->receivePacket();

            auto command = commandFactory_.createCommand(frame);
            command->accept(commandHandler_);

            auto response = commandHandler_.getResponse();
            socket_->sendData(response->getFrameBytes());
        }
        catch (exception &e)
        {
            // 1. socket is disabled
            // 2. factory can't create a command

            // TO DO: Check what type of exception was registered.
            if(runListenThread_)
            {
                // If socket has been closed or the connection has been lost, the thread has to be closed.
                runListenThread_ = false;
            }
        }


    }
}

bool ClientThreadTCP::checkListenEnable()
{
    return runListenThread_;
}