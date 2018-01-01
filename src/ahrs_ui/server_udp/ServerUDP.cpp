#include <ahrs_ui/server_udp/ServerUDP.h>

#include <iostream>

using namespace std;
using namespace communication;

ServerUDP::ServerUDP(uint16_t port)
    : port_(port),
      runListenThread_(false)
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

    cout << "Server UDP starts listen" << endl;
    while(runListenThread_)
    {
        try
        {
            const auto frame = socket_->receivePacket();

            cout << "Server UDP get packet" << endl;

            const auto data = dataFactory_.createCommand(frame);
            data->accept(dataVisitor_);

        }
        catch (exception &e)
        {

        }
    }
}
