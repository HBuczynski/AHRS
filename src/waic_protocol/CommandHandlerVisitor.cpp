#include "CommandHandlerVisitor.h"
#include "InitConnectionExecutor.h"
#include "EndConnectionExecutor.h"

#include <waic_server/ClientThreadTCP.h>

using namespace std;
using namespace communication;

CommandHandlerVisitor::CommandHandlerVisitor()
{
}

CommandHandlerVisitor::~CommandHandlerVisitor()
{
}

void CommandHandlerVisitor::initializeCurrentClient(ClientThreadTCP *client)
{
    currentClient_ = client;
}

void CommandHandlerVisitor::initializeCallbackFunction(CallbackFunctions callbackFunctions)
{
    callbackFunctions_ = callbackFunctions;
}

void CommandHandlerVisitor::visit(InitConnectionCommand &command)
{
    InitConnectionExecutor initConnectionExecutor(callbackFunctions_.insertNewClient);

    response_ = initConnectionExecutor.execute(command.getFrameBytes(), currentClient_->getID());
}

void CommandHandlerVisitor::visit(EndConnectionCommand &command)
{
    EndConnectionExecutor endConnectionExecutor(callbackFunctions_.removeClient, currentClient_);

    response_ = endConnectionExecutor.execute(command.getFrameBytes(), currentClient_->getID());
}

std::shared_ptr<Response> CommandHandlerVisitor::getResponse()
{
    return shared_ptr<Response>();
}