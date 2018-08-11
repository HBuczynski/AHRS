#include "ResponseHandlerVisitor.h"

using namespace std;
using namespace communication;
using namespace utility;

ResponseHandlerVisitor::ResponseHandlerVisitor()
    : logger_(Logger::getInstance())
{}

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

}
