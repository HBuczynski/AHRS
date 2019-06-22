#include "InterResponseVisitor.h"

using namespace utility;
using namespace communication;

InterResponseVisitor::InterResponseVisitor()
    : logger_(Logger::getInstance())
{}

InterResponseVisitor::~InterResponseVisitor()
{}

void InterResponseVisitor::visit(EthAckFeederResponse& command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-INTCOM- CommandHandler :: Received") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
