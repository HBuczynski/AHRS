#include "ClientThreadTCP.h"

#include <interfaces/wireless_commands/Command.h>

#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;

ClientThreadTCP::ClientThreadTCP(unique_ptr<SendStreamTCP> socket, shared_ptr<ClientUDPManager> clientUDPManager)
    : runListenThread_(false),
      socket_(std::move(socket)),
      clientUDPManager_(clientUDPManager),
      logger_(Logger::getInstance())
{
    initializeCommandHandler();
}

ClientThreadTCP::~ClientThreadTCP()
{
    stopListen();
}

void ClientThreadTCP::initializeCommandHandler()
{
    commandHandler_.initializeClientUDPManager(clientUDPManager_);
    commandHandler_.initializeCurrentClient(this);
}

void ClientThreadTCP::setID(uint32_t id)
{
    id_ = id;
}

uint32_t ClientThreadTCP::getID() const
{
    return id_;
}

void ClientThreadTCP::startListen()
{
    runListenThread_ = true;
    listenThread_ = thread(&ClientThreadTCP::runListen, this);
}

// TO DO: check reset on socket !!
void ClientThreadTCP::stopListen()
{
    if(socket_.get() != nullptr)
    {
        socket_.reset();
    }
    runListenThread_ = false;

    if(listenThread_.joinable())
    {
        listenThread_.join();
    }
}

void ClientThreadTCP::runListen()
{
    if(logger_.isInformationEnable())
    {
        const string message = string("ClientThreadTCP :: ClientdID -") + to_string(getID()) + string("- starts listening.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    // to do: zamkniecie gdy nie otrzymamy pakietu
    while(runListenThread_)
    {
        try
        {
            const auto frame = socket_->receivePacket();

            const auto command = commandFactory_.createCommand(frame);
            command->accept(commandHandler_);

            const auto response = commandHandler_.getResponse();
            socket_->sendData(response->getFrameBytes());
        }
        catch (exception &e)
        {

            if(logger_.isErrorEnable() && runListenThread_ && (e.what()) == string("Cannot receive packet."))
            {
                const string message = string("ClientThreadTCP (runListenThread) :: ClientdID -") + to_string(getID()) +
                                 string("-. Received exception: ") + e.what();
                logger_.writeLog(LogType::ERROR_LOG, message);

                const string message2 = string("ClientThreadTCP (runListenThread) :: ClientdID -") + to_string(getID()) +
                                       string("-. Connection is terminated.");
                logger_.writeLog(LogType::ERROR_LOG, message2);

                runListenThread_ = false;

                if(socket_.get() != nullptr)
                {
                    socket_.reset();
                }
            }

            if(logger_.isErrorEnable() && runListenThread_ )
            {
                const string message = string("ClientThreadTCP (runListenThread) :: ClientdID -") + to_string(getID()) +
                                       string("-. Received exception: ") + e.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

bool ClientThreadTCP::checkListenEnable()
{
    return runListenThread_;
}