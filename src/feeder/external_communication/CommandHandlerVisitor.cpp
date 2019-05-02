#include "CommandHandlerVisitor.h"

#include <interfaces/communication_process_feeder/StateNotification.h>
#include <interfaces/communication_process_feeder/FeederWirelessWrapperCommand.h>
#include <interfaces/wireless_responses/DataResponse.h>
#include <interfaces/wireless_responses/AckResponse.h>
#include <interfaces/wireless_responses/PlanesDatasetResponse.h>
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <interfaces/wireless_measurement_commands/ImuData.h>
#include <interfaces/wireless_responses/CurrentStateResponse.h>
#include <interfaces/wireless_responses/BITsResponse.h>
#include <interfaces/wireless_responses/ResponseFactory.h>

#include <feeder/external_communication/ClientThreadTCP.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <utility/Utility.h>
#include <iostream>
#include <algorithm>

#include <utility/BytesConverter.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

extern char **environ;


CommandHandlerVisitor::CommandHandlerVisitor()
    : sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
      logger_(Logger::getInstance())
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

void CommandHandlerVisitor::visit(SetPlaneCommand &command)
{
    response_ = std::make_unique<AckResponse>(AckType::OK);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    // Send information to main process about plane state.
    auto wrapper = FeederWirelessWrapperCommand(command.getFrameBytes());
    auto wrapperPacket = wrapper.getFrameBytes();
    clientUDPManager_->sendToMainProcess(wrapperPacket);

    // Send information to main process to change state.
    auto notification = StateNotification(FeederStateCode::CALLIBATION);
    auto packet = notification.getFrameBytes();
    clientUDPManager_->sendToMainProcess(packet);
}

void CommandHandlerVisitor::visit(CalibrateDataCommand& command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received - ") + command.getName() +
                                    std::string(". From ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    const auto frame = externalSharedMemory_->read();
    ResponseFactory responseFactory;

    response_ = responseFactory.createCommand(frame);
}

void CommandHandlerVisitor::visit(CallibrateMagnetometerCommand &command)
{
    response_ = std::make_unique<AckResponse>(AckType::OK);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + string(", action: ") +
                                    to_string(static_cast<int>(command.getMagAction())) + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}


void CommandHandlerVisitor::visit(CalibrateAccelerometerCommand& command)
{
    response_ = std::make_unique<AckResponse>(AckType::OK);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received - ") + command.getName() + ". Action: " +
                                    to_string(static_cast<int>(command.getAction()))+ std::string(". From ClientID -") +
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

void CommandHandlerVisitor::visit(StartAcquisitionCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
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

void CommandHandlerVisitor::visit(CalibrationStatusCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- CommandHandler :: Received") + command.getName() + std::string(" from ClientID -") +
                                    std::to_string(currentClient_->getID()) + std::string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CurrentStateCommand &command)
{
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

void CommandHandlerVisitor::initializeExternalSharedMemory()
{
    try
    {
        externalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-EXTCOMM- CommandHandlerVisitor:: External SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOMM- CommandHandlerVisitor :: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}



