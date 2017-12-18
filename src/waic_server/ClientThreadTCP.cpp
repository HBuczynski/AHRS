#include "ClientThreadTCP.h"

#include <waic_protocol/Command.h>

using namespace std;
using namespace communication;

ClientThreadTCP::ClientThreadTCP(unique_ptr<SendStreamTCP> socket, CallbackFunctions callbackFunctions)
    : socket_(std::move(socket)),
      callbackFunctions_(callbackFunctions),
      runListenThread_(false)
{

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
    runListenThread_ = false;
}

void ClientThreadTCP::runListen()
{
    while(runListenThread_)
    {
        auto frame = socket_->receivePacket();

        (commandFactory_.createCommand(frame))->accept(commandHandler_);
        auto response = commandHandler_.getResponse();

        socket_->sendData(response->getFrameBytes());
    }
}

bool ClientThreadTCP::checkListenEnable()
{
    return runListenThread_;
}