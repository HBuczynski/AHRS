#include "EthServerUDP.h"
#include <config_reader/ConfigurationReader.h>

#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

EthServerUDP::EthServerUDP(uint16_t port)
    : port_(port),
      runListenThread_(false),
      sharedMemoryParameters_(config::ConfigurationReader::getFeederSharedMemory(config::FEEDER_PARAMETERS_FILE_PATH)),
      logger_(Logger::getInstance())
{}

EthServerUDP::~EthServerUDP()
{
    if (runListenThread_)
        stopListening();
}

void EthServerUDP::initializeSharedMemory()
{
    try
    {
        internalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-EXTCOMM- EthServerUDP:: Internal SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOMM- EthServerUDP :: Internal shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void EthServerUDP::startListening()
{
    runListenThread_ = true;
    listenThread_ = thread(&EthServerUDP::listen, this);
}

void EthServerUDP::stopListening()
{
    if (runListenThread_)
    {
        runListenThread_ = false;
        socket_->~ListenDatagramUDP();

        if (listenThread_.joinable())
            listenThread_.join();
    }
}

void EthServerUDP::listen()
{
    socket_.reset();
    socket_ = make_unique<ListenDatagramUDP>(port_);

    if(logger_.isInformationEnable())
    {
        const string message = string("-ExtCOMM- EthServerUDP :: Server starts listening on port: ") + to_string(port_);
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    while(runListenThread_)
    {
        try
        {
            auto frame = socket_->receivePacket();
            internalSharedMemory_->write(frame);
        }
        catch (exception &e)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-ExtCOMM- EthServerUDP :: Received exception: ") + e.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
