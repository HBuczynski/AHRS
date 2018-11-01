#include "CommandHandlerVisitor.h"

#include <interfaces/wireless_responses/DataResponse.h>
#include <interfaces/wireless_responses/AckResponse.h>
#include <interfaces/wireless_responses/PlanesDatasetResponse.h>
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <interfaces/wireless_measurement_commands/ImuData.h>
#include <interfaces/wireless_responses/CurrentStateResponse.h>
#include <interfaces/wireless_responses/BITsResponse.h>

#include <config_reader/ConfigurationReader.h>
#include <feeder/external_communication/ClientThreadTCP.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <iostream>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

CommandHandlerVisitor::CommandHandlerVisitor()
    :   //sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
        logger_(Logger::getInstance())
{
//    initializedSharedMemory();
}

CommandHandlerVisitor::~CommandHandlerVisitor()
{}

//void CommandHandlerVisitor::initializedSharedMemory()
//{
//    try
//    {
//        // Creating shared memory's mutex.
//        sharedMemoryMutex_ = std::make_unique<named_mutex>(open_only, sharedMemoryParameters_.externalMemoryName.c_str());
//        // Creating shared memory.
//        sharedMemory_ = std::make_unique<shared_memory_object>(open_only, sharedMemoryParameters_.externalMemoryName.c_str(), read_write);
//        mappedMemoryRegion_ = std::make_unique<mapped_region>(*sharedMemory_, read_write);
//    }
//    catch(interprocess_exception &ex)
//    {
//        if (logger_.isErrorEnable()) {
//            const std::string message = std::string("CommandHandlerVisitor ::") + ex.what();
//            logger_.writeLog(LogType::ERROR_LOG, message);
//        }
//    }
//}

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

    response_ = std::make_unique<PlanesDatasetResponse>(ConfigurationReader::getAircraftDatabase(FEEDER_AIRCRAFTS_DATABASE_FILE_PATH));
}

void CommandHandlerVisitor::visit(EndConnectionCommand &command)
{
    clientUDPManager_->removeClient(currentClient_->getID());
    currentClient_->stopListen();

    response_ = std::make_unique<AckResponse>(AckType::OK);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CallibrateMagnetometerCommand &command)
{
    const auto planeName = command.getPlaneName();
    const auto planeStatus = command.getPlaneStatus();

    clientUDPManager_->startCalibration(planeName, planeStatus);
    response_ = std::make_unique<AckResponse>(AckType::OK);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CalibrationStatusCommand &command)
{
//    switch (clientUDPManager_->getCurrentState())
//    {
//
//
//    }

    //TODO

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(StartAcquisitionCommand &command)
{
    clientUDPManager_->startDataSending();

    if(clientUDPManager_->getCurrentState() == FeederExternalStateCode::MASTER_SENDING)
    {
        response_ = std::make_unique<AckResponse>(AckType::OK);
    }
    else
    {
        response_ = std::make_unique<AckResponse>(AckType::FAIL);
    }

    flightDataManager_->startFlightDataTransmission();

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CurrentStateCommand &command)
{
    response_ = std::make_unique<CurrentStateResponse>(clientUDPManager_->getCurrentState());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CollectDataCommand &command)
{

}

void CommandHandlerVisitor::visit(RemovePlaneDataCommand &command)
{

}

void CommandHandlerVisitor::visit(SetPlaneMagnetometerCommand &command)
{

}

void CommandHandlerVisitor::visit(PerformBITsCommand& command)
{
    response_ = std::make_unique<BITsResponse>(1, UICommunicationMode::MASTER);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

std::unique_ptr<Response> CommandHandlerVisitor::getResponse()
{
    return std::move(response_);
}

void CommandHandlerVisitor::initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager)
{
    clientUDPManager_ = clientUDPManager;
    flightDataManager_= make_shared<FlightDataManager>(clientUDPManager);
}

void CommandHandlerVisitor::initializeCurrentClient(ClientThreadTCP *client)
{
    currentClient_ = client;
}





