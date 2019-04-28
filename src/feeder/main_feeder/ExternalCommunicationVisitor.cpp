#include "ExternalCommunicationVisitor.h"
#include "ApplicationManager.h"

using namespace std;
using namespace main_process;
using namespace utility;
using namespace communication;

ExternalCommunicationVisitor::ExternalCommunicationVisitor()
    : logger_(Logger::getInstance())
{}

ExternalCommunicationVisitor::~ExternalCommunicationVisitor()
{}

void ExternalCommunicationVisitor::registerApplicationManager(ApplicationManager *appManager)
{
    appManager_ = appManager;
}

void ExternalCommunicationVisitor::visit(const CalibrateMgnDemandCommand &command)
{

}

void ExternalCommunicationVisitor::visit(const CalibrationStatusNotification &command)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ExternalCommInterprocessVisitor :: Received - CalibrationStatusNotification");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ExternalCommunicationVisitor::visit(const communication::StateNotification& command)
{
    const auto type = static_cast<FeederStateCode>(command.getStateCode());

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ExternalCommInterprocessVisitor :: Received - StateNotification - ")
                + to_string(static_cast<int>(command.getStateCode()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    switch (type)
    {
        case FeederStateCode::REGISTERED_USERS :
            appManager_->handleEvent("RUN_REGISTARTION");
            break;
        case FeederStateCode::SETTINNG :
            appManager_->handleEvent("GET_SETTINGS");
            break;
        default:
            break;
    }
}
