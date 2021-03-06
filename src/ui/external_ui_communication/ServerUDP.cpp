#include <ui/external_ui_communication/ServerUDP.h>

#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;

ServerUDP::ServerUDP(uint16_t port, CommunicationManagerUI *communicationManagerUI)
    : port_(port),
      runListenThread_(false),
      dataVisitor_(communicationManagerUI),
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
        const string message = string("-ExtCOMM- ServerUDP :: Server starts listening on port: ") + to_string(port_);
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
                const string message = string("-ExtCOMM- ServerUDP :: Received exception: ") + e.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void ServerUDP::registerDbParameters(uint32_t hash, const std::string& name)
{
    dataVisitor_.initializeDB(hash, name);
}
