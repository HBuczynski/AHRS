#include <config_reader/ConfigurationReader.h>
#include "ResponseHandlerVisitor.h"

#include <interfaces/communication_process_ui/ReceivingDataNotification.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

ResponseHandlerVisitor::ResponseHandlerVisitor()
    :   uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
        logger_(Logger::getInstance())
{
    initializeMessageQueue();
}

ResponseHandlerVisitor::~ResponseHandlerVisitor()
{}

void ResponseHandlerVisitor::visit(AckResponse &data)
{
    if(logger_.isInformationEnable())
    {
        string message;
        if (data.getAckType() == AckType::OK) {
            message = string("ResponseHandlerVisitor :: Received AckResponse, ackTYPE: OK");
        } else {
            message = string("ResponseHandlerVisitor :: Received AckResponse, ackTYPE: FAIL");
        }

        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ResponseHandlerVisitor::visit(DataResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("ResponseHandlerVisitor :: Received DataResponse, data: ") + data.getData();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ResponseHandlerVisitor::visit(CalibratingStatusResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("ResponseHandlerVisitor :: Received CalibratingStatusResponse.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ResponseHandlerVisitor::visit(PlanesDatasetResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("ResponseHandlerVisitor :: Received PlanesDatasetResponse.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ResponseHandlerVisitor::visit(CurrentStateResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("ResponseHandlerVisitor :: Received CurrentStateResponse.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ResponseHandlerVisitor::visit(BITsResponse& data)
{
    ReceivingDataNotification dataNotification(data.getFrameBytes());
    sendMessage(dataNotification.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const string message = string("ResponseHandlerVisitor :: Received BITsResponse.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ResponseHandlerVisitor::initializeMessageQueue()
{
    try
    {
        sendingMessageQueue_ = make_unique<message_queue>(open_only, uiMessageQueuesParameters_.mainProcessQueueName.c_str());
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("ResponseHandlerVisitor:: During openning main queue - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("ResponseHandlerVisitor:: Main massage queue initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ResponseHandlerVisitor::sendMessage(std::vector<uint8_t> msg)
{
    sendingMessageQueue_->send(msg.data(), msg.size(), 0);

    if (logger_.isInformationEnable())
    {
        const std::string message = string("ResponseHandlerVisitor:: Send msg to main process.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
