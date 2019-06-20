#include "EthCommandHandlerVisitor.h"

#include "ClientThreadTCP.h"
#include "ClientUDPManager.h"

using namespace std;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

EthCommandHandlerVisitor::EthCommandHandlerVisitor()
    : logger_(Logger::getInstance())
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

void EthCommandHandlerVisitor::initializeMainMsgQueue()
{
    try
    {
        mainMsgQueue_ = make_shared<MessageQueueWrapper>(msgQueuesParametes_.mainProcessQueueName, msgQueuesParametes_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-INTCOM- EthCommandHandlerVisitor:: ") + msgQueuesParametes_.mainProcessQueueName + (" queue has not been initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-INTCOM- EthCommandHandlerVisitor:: Main message queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void EthCommandHandlerVisitor::visit(EthChangeStateCommand& command)
{

}

void EthCommandHandlerVisitor::visit(EthHandshakeCommand& command)
{

}

void EthCommandHandlerVisitor::visit(EthInitConnectionCommand& command)
{

}

std::unique_ptr<EthFeederResponse> EthCommandHandlerVisitor::getResponse()
{
    return std::move(response_);
}
