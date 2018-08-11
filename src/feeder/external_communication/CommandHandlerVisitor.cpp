#include "CommandHandlerVisitor.h"

#include <interfaces/wireless_responses/DataResponse.h>
#include <interfaces/wireless_measurement_commands/ImuData.h>

#include <config_reader/ConfigurationReader.h>
#include <feeder/external_communication/ClientThreadTCP.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <iostream>


using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

CommandHandlerVisitor::CommandHandlerVisitor()
    :   sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
        logger_(Logger::getInstance())
{
    initializedSharedMemory();
}

CommandHandlerVisitor::~CommandHandlerVisitor()
{}

void CommandHandlerVisitor::initializedSharedMemory()
{
    try
    {
        // Creating shared memory's mutex.
        named_mutex::remove(sharedMemoryParameters_.externalMemoryName.c_str());
        sharedMemoryMutex_ = std::make_unique<named_mutex>(create_only, sharedMemoryParameters_.externalMemoryName.c_str());

        // Creating shared memory.
        shared_memory_object::remove(sharedMemoryParameters_.externalMemoryName.c_str());
        sharedMemory_ = std::make_unique<shared_memory_object>(create_only, sharedMemoryParameters_.externalMemoryName.c_str(), read_write);

        // Resize shared memory.
        sharedMemory_->truncate(sharedMemoryParameters_.sharedMemorySize);
        mappedMemoryRegion_ = std::make_unique<mapped_region>(*sharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable()) {
            const std::string message = std::string("External Communication ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void CommandHandlerVisitor::visit(InitConnectionCommand &command)
{
    auto newClient = std::make_shared<ClientUDP>(command.getPort(), command.getAddress());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received InitConnectionCommand from ClientID -") +
                std::to_string(currentClient_->getID())
                         + std::string("-. Command data: port-") + std::to_string(command.getPort()) + std::string("; address-") +
                         command.getAddress();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    clientUDPManager_->insertNewClient(make_pair((newClient), currentClient_->getID()));

    ///TODO: resend plane database
    response_ = std::make_unique<DataResponse>("OK");
}

void CommandHandlerVisitor::visit(EndConnectionCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received EndConnectionCommand from ClientID -") +
                std::to_string(currentClient_->getID())
                         + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    clientUDPManager_->removeClient(currentClient_->getID());
    currentClient_->stopListen();

    response_ = std::make_unique<DataResponse>("OK");
}

void CommandHandlerVisitor::visit(CallibrateMagnetometerCommand &command)
{
    const auto planeName = command.getPlaneName();
    const auto planeStatus = command.getPlaneStatus();

    clientUDPManager_->startCalibration(planeName, planeStatus);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received CallibrateMagnetometerCommand from ClientID -") +
                std::to_string(currentClient_->getID())
                         + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    //TODO: response
}

void CommandHandlerVisitor::visit(CollectDataCommand &command)
{
    ImuData imuData(12);
    clientUDPManager_->broadcast(imuData.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received CollectDataCommand from ClientID -") +
                std::to_string(currentClient_->getID())
                         + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    response_ = std::make_unique<DataResponse>("OK");
}

void CommandHandlerVisitor::visit(RemovePlaneDataCommand &command)
{

}

void CommandHandlerVisitor::visit(SetPlaneMagnetometerCommand &command)
{

}

std::unique_ptr<Response> CommandHandlerVisitor::getResponse()
{
    return std::move(response_);
}

void CommandHandlerVisitor::initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager)
{
    clientUDPManager_ = clientUDPManager;
}

void CommandHandlerVisitor::initializeCurrentClient(ClientThreadTCP *client)
{
    currentClient_ = client;
}

