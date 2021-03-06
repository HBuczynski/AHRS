#include "FMVisitor.h"

using namespace std;
using namespace utility;
using namespace main_process;
using namespace communication;

FMVisitor::FMVisitor()
    :   logger_(Logger::getInstance())
{}

FMVisitor::~FMVisitor()
{}

void FMVisitor::initializeCommunicationProcess(CommunicationProcessesHandler *communicationProcessesHandler)
{
    communicationProcessesHandler_ = communicationProcessesHandler;
}

void FMVisitor::initializeGuiProcess(GuiProcessHandler *guiProcessHandler)
{
    guiProcessHandler_ = guiProcessHandler;
}

void FMVisitor::visit(const FMResetCommunicationProcessCommand& command)
{
    communicationProcessesHandler_->resetProcess(command.getMode());
    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN-FMVisitor:: Received - FMResetCommunicationProcessCommand") + to_string(static_cast<int>(command.getMode()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void FMVisitor::visit(const FMRestartChangeMasterCommand& command)
{
    communicationProcessesHandler_->restartMasterProcessAndChange(command.getSystemState());
}

void FMVisitor::visit(const communication::FMChangeChannelCommand& command)
{

}
