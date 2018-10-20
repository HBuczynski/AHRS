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

}

void MainProcessHandlerVisitor::visit(ShutdownCommand &command)
{

}

void MainProcessHandlerVisitor::visit(ReconnectCommand &command)
{

}

void MainProcessHandlerVisitor::visit(SendingDataCommand &command)
{
    auto com = wirelessCommandFactory_.createCommand(command.getDataFrame());

    communicationManager_->sendCommands(move(com));
}
