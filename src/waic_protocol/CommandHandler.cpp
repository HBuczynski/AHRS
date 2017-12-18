#include "CommandHandler.h"
#include "InitConnectionExecutor.h"
#include "EndConnectionExecutor.h"

#include <waic_server/ClientThreadTCP.h>

using namespace std;
using namespace communication;

CommandHandler::CommandHandler()
{

}

CommandHandler::~CommandHandler()
{

}

void CommandHandler::initializeCurrentClient(ClientThreadTCP *client)
{
    currentClient_ = client;
}

void CommandHandler::initializeCallbackFunction(CallbackFunctions callbackFunctions)
{
    callbackFunctions_ = callbackFunctions;
}

void CommandHandler::visit(InitConnectionCommand &command)
{
    InitConnectionExecutor initConnectionExecutor(callbackFunctions_.insertNewClient);

    response_ = initConnectionExecutor.execute(command.getFrameBytes(), currentClient_->getID());
}

void CommandHandler::visit(EndConnectionCommand &command)
{
    EndConnectionExecutor endConnectionExecutor(callbackFunctions_.removeClient);

    response_ = endConnectionExecutor.execute(command.getFrameBytes(), currentClient_->getID());
}

std::shared_ptr<Response> CommandHandler::getResponse()
{
    return shared_ptr<Response>();
}