#include <ahrs_ui/server_udp/Server.h>


using namespace std;
using namespace communication;

Server::Server(uint16_t port)
    : port_(port),
      runListenThread_(false)
{}

Server::~Server()
{
    if (runListenThread_)
    {
        stopListening();
    }
}

void Server::startListening()
{
    runListenThread_ = true;
    listenThread_ = thread(&Server::listen, this);
}

void Server::stopListening()
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

void Server::listen()
{
    socket_.reset();
    socket_ = make_unique<ListenDatagramUDP>(port_);

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

        }
    }
}
