#include "EthCommandHandlerVisitor.h"

#include <interfaces/communication_process_feeder/StateNotification.h>
#include <interfaces/ethernet_feeder/EthAckFeederResponse.h>
#include <config_reader/ConfigurationReader.h>

#include <interfaces/wireless_measurement_commands/FeederData.h>
#include <interfaces/wireless_measurement_commands/MeasuringDataFactory.h>

#include "ClientThreadTCP.h"
#include "ClientUDPManager.h"

using namespace std;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

EthCommandHandlerVisitor::EthCommandHandlerVisitor()
    : sharedMemoryParameters_(config::ConfigurationReader::getFeederSharedMemory(config::FEEDER_PARAMETERS_FILE_PATH)),
      logger_(Logger::getInstance())
{}

EthCommandHandlerVisitor::~EthCommandHandlerVisitor()
{}

void EthCommandHandlerVisitor::initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager)
{
    clientUDPManager_ = clientUDPManager;
}

void EthCommandHandlerVisitor::initializeCurrentClient(ClientThreadTCP *client)
{
    currentClient_ = client;
}

void EthCommandHandlerVisitor::initializeSharedMemory()
{
    try
    {
        internalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName);
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
        const std::string message = std::string("-INTCOM- EthCommandHandlerVisitor :: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void EthCommandHandlerVisitor::visit(EthChangeStateCommand& command)
{
    const auto stateType = command.getFeederState();

    switch (stateType) {
        case FeederStateCode::REGISTERED_USERS :
        case FeederStateCode::SETTINNG :
        case FeederStateCode::CALLIBATION :
        case FeederStateCode::PERFORM_BIT :
        {
            StateNotification notification(stateType);
            auto packet = notification.getFrameBytes();
            clientUDPManager_->sendToMainProcess(packet);
            break;
        }
        case FeederStateCode::MAIN_ACQ :
        {
            StateNotification notification(stateType);
            auto packet = notification.getFrameBytes();
            clientUDPManager_->sendToMainProcess(packet);

            runAcq_ = true;
            acqThread_ = thread(&EthCommandHandlerVisitor::startDataSending, this);

            break;
        }
        case FeederStateCode::STOP_ACQ :
        {
            StateNotification notification(stateType);
            auto packet = notification.getFrameBytes();
            clientUDPManager_->sendToMainProcess(packet);

            stopDataSending();
            break;
        }
        default:
            break;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-INTCOM- EthCommandHandlerVisitor :: Received EthChangeStateCommand - state: ") + to_string(static_cast<int>(stateType));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    response_ = std::make_unique<EthAckFeederResponse>();
}

void EthCommandHandlerVisitor::visit(EthHandshakeCommand& command)
{

}

void EthCommandHandlerVisitor::visit(EthInitConnectionCommand& command)
{
    clientUDP_ = std::make_unique<ClientUDP>(command.getServerListenUDPPort(), command.getServerAddress());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-INTCOM- EthCommandHandlerVisitor :: Received InitConnectionCommand from ClientID -") +
                std::to_string(currentClient_->getID())
                         + std::string("-. Command data: port-") + std::to_string(command.getServerListenUDPPort()) + std::string("; address-") +
                         command.getServerAddress();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    //Send information to main process
    auto notification = StateNotification(FeederStateCode::SETTINNG);
    auto packet = notification.getFrameBytes();
    clientUDPManager_->sendToMainProcess(packet);

    response_ = std::make_unique<EthAckFeederResponse>();
}

void EthCommandHandlerVisitor::startDataSending()
{
    MeasuringDataFactory dataFactory;

    while (runAcq_)
    {
        try
        {
            auto frame = internalSharedMemory_->read();
            auto dataCommand = static_pointer_cast<FeederData, MeasuringData>(dataFactory.createCommand(frame));

            if(dataCommand->getMeasuringType() != MeasuringType::FLIGHT_DATA)
                break;
            clientUDP_->sendData(frame);
        }
        catch (exception &e)
        {
            if(logger_.isErrorEnable() )
            {
                const string message = string("-EXTCOM- FlightDataManager:: In catch function.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

void EthCommandHandlerVisitor::stopDataSending()
{
    runAcq_ = false;

    if (acqThread_.joinable())
        acqThread_.join();
}

std::unique_ptr<EthFeederResponse> EthCommandHandlerVisitor::getResponse()
{
    return std::move(response_);
}
