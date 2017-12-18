#include "InitConnectionExecutor.h"
#include <waic_protocol/DataResponse.h>

#include <waic_protocol/InitConnectionCommand.h>
#include <waic_protocol/CommandFactory.h>

using namespace std;
using namespace communication;

InitConnectionExecutor::InitConnectionExecutor(function<void (pair<shared_ptr<Client>, uint8_t>) > callbackFunction)
    : insertNewClient(callbackFunction)
{

}

InitConnectionExecutor::~InitConnectionExecutor()
{
}

shared_ptr<Response> InitConnectionExecutor::execute(const vector<uint8_t> &commandInBytes, uint8_t clientID)
{
    CommandFactory commandFactory;

    shared_ptr<InitConnectionCommand> initConnectionCommand = dynamic_pointer_cast<InitConnectionCommand, Command >(commandFactory.createCommand(commandInBytes));

    shared_ptr<Client> newClient = make_shared<Client>(initConnectionCommand->getPort(), initConnectionCommand->getAddress());
    insertNewClient(make_pair(newClient, clientID));

    shared_ptr<Response> response = make_shared<DataResponse>("OK");

    return response;
}
