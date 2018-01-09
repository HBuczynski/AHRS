#include <ahrs_ui/server_udp/ServerUDP.h>

#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;

ServerUDP::ServerUDP(uint16_t port)
    : port_(port),
      runListenThread_(false),
      logger_(Logger::getInstance())
{}

ServerUDP::~ServerUDP()
{
    if (runListenThread_)
    {
        stopListening();
    }
}

void ServerUDP::startListening()
{
    runListenThread_ = true;
    listenThread_ = thread(&ServerUDP::listen, this);
}

void ServerUDP::stopListening()
{
    if (runListenThread_)
    {
        runListenThread_ = false;
        socket_->~ListenDatagramUDP();

        if (listenThread_.joinable())
        {
            listenThread_.join();
        }
    }
}

void ServerUDP::listen()
{
    socket_.reset();
    socket_ = make_unique<ListenDatagramUDP>(port_);

    if(logger_.isInformationEnable())
    {
        const string message = string("ServerUDP :: Server starts listening.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    while(runListenThread_)
    {
        try
        {
            const auto frame = socket_->receivePacket();

            const auto data = dataFactory_.createCommand(frame);
            data->accept(dataVisitor_);

        }
        catch (exception &e)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("ServerUDP :: Received exception: ") + e.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
}
