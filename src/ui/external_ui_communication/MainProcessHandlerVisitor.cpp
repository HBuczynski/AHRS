#include <interfaces/wireless_commands/PerformBITsCommand.h>
#include "MainProcessHandlerVisitor.h"

using namespace std;
using namespace utility;
using namespace communication;

MainProcessHandlerVisitor::MainProcessHandlerVisitor(std::shared_ptr<CommunicationManagerUI> communicationManager)
    : communicationManager_(communicationManager),
      logger_(Logger::getInstance())
{}

MainProcessHandlerVisitor::~MainProcessHandlerVisitor()
{}

void MainProcessHandlerVisitor::visit(UIChangeModeCommand &command)
{
    communicationManager_->setMode(command.getMode());

    if(logger_.isInformationEnable())
    {
        const string message = string("-ExtCOMM- MainProcessHandlerVisitor :: Received ") + command.getName() + " " + to_string(static_cast<int>(command.getMode()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    };
}

void MainProcessHandlerVisitor::visit(ShutdownCommand &command)
{}

void MainProcessHandlerVisitor::visit(ReconnectCommand &command)
{}

void MainProcessHandlerVisitor::visit(SendingDataCommand &command)
{
    auto com = wirelessCommandFactory_.createCommand(command.getDataFrame());
    communicationManager_->sendCommands(move(com));
}

void MainProcessHandlerVisitor::visit(DatabaseHashCommand& command)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-ExtCOMM- MainProcessHandlerVisitor :: Received ") + command.getName() +
                string(". Hash: ") + to_string(command.getHash()) +
                string(". Name: ") + command.getDbName();

        logger_.writeLog(LogType::INFORMATION_LOG, message);
    };

    communicationManager_->setDBParameters(command.getHash(), command.getDbName());
}
