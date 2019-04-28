#include "CommandHandlerVisitor.h"

#include <interfaces/communication_process_feeder/StateNotification.h>
#include <interfaces/wireless_responses/DataResponse.h>
#include <interfaces/wireless_responses/AckResponse.h>
#include <interfaces/wireless_responses/PlanesDatasetResponse.h>
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <interfaces/wireless_measurement_commands/ImuData.h>
#include <interfaces/wireless_responses/CurrentStateResponse.h>
#include <interfaces/wireless_responses/BITsResponse.h>

#include <feeder/external_communication/ClientThreadTCP.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <utility/Utility.h>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

CommandHandlerVisitor::CommandHandlerVisitor()
    :  logger_(Logger::getInstance())
{}

CommandHandlerVisitor::~CommandHandlerVisitor()
{}

void CommandHandlerVisitor::visit(InitConnectionCommand &command)
{
    auto newClient = std::make_shared<ClientUDP>(command.getPort(), command.getAddress());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received InitConnectionCommand from ClientID -") +
                std::to_string(currentClient_->getID())
                         + std::string("-. Command data: port-") + std::to_string(command.getPort()) + std::string("; address-") +
                         command.getAddress();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    clientUDPManager_->insertNewClient(make_pair((newClient), currentClient_->getID()));

    //Send information to main process
    auto notification = StateNotification(FeederStateCode::SETTINNG);
    auto packet = notification.getFrameBytes();
    clientUDPManager_->sendToMainProcess(packet);

    response_ = std::make_unique<PlanesDatasetResponse>(getPlanesDataset());
}

void CommandHandlerVisitor::visit(EndConnectionCommand &command)
{
    clientUDPManager_->removeClient(currentClient_->getID());
    currentClient_->stopListen();

    response_ = std::make_unique<AckResponse>(AckType::OK);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CallibrateMagnetometerCommand &command)
{

    response_ = std::make_unique<AckResponse>(AckType::OK);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
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
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(StartAcquisitionCommand &command)
{
//    clientUDPManager_->startDataSending();

//    if(clientUDPManager_->getCurrentState() == FeederExternalStateCode::MASTER_SENDING)
//    {
//        response_ = std::make_unique<AckResponse>(AckType::OK);
//    }
//    else
//    {
//        response_ = std::make_unique<AckResponse>(AckType::FAIL);
//    }

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CurrentStateCommand &command)
{
    //response_ = std::make_unique<CurrentStateResponse>(clientUDPManager_->getCurrentState());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
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

void CommandHandlerVisitor::visit(SetPlaneCommand &command)
{
    const auto planeName = command.getPlaneName();
    const auto dataset = Utility::getFilesNamesInDir(FEEDER_AIRCRAFTS_DATABASE_PATH);

    //TO DO
    if(std::find(dataset.cbegin(), dataset.cend(), planeName) != dataset.cend())
    {
        CalibrationConfiguration callibration;
        response_ = make_unique<CalibratingStatusResponse>(callibration, 0);
    }
    else
    {
        CalibrationConfiguration callibration;
        response_ = make_unique<CalibratingStatusResponse>(callibration, 0);
    }

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(PerformBITsCommand& command)
{
    response_ = std::make_unique<BITsResponse>(1, UICommunicationMode::MASTER);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CalibrateAccelerometerCommand& command)
{
    //response_ = std::make_unique<CurrentStateResponse>(clientUDPManager_->getCurrentState());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
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
}

void CommandHandlerVisitor::initializeCurrentClient(ClientThreadTCP *client)
{
    currentClient_ = client;
}

std::string CommandHandlerVisitor::getPlanesDataset()
{
    const auto planeNames = Utility::getFilesNamesInDir(FEEDER_AIRCRAFTS_DATABASE_PATH);
    string nameMsg;

    for(auto plane : planeNames)
    {
        nameMsg += plane;
        nameMsg += ",";
    }

    return nameMsg.substr(0, nameMsg.size() - 1);
}



