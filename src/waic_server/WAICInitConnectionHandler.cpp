#include "WAICInitConnectionHandler.h"
#include <waic_protocol/WAICDataResponse.h>

#include <waic_protocol/WAICInitConnectionCommand.h>

using namespace std;
using namespace communication;

WAICInitConnectionHandler::WAICInitConnectionHandler(function<void (pair<shared_ptr<WAICClient>, uint8_t>) > callbackFunction)
    : insertNewClient(callbackFunction)
{

}

WAICInitConnectionHandler::~WAICInitConnectionHandler()
{
}

shared_ptr<WAICResponse> WAICInitConnectionHandler::handler(const vector<uint8_t> &vec, uint8_t clientID)
{
    WAICInitConnectionCommand initConnectionCommand(vec);

    shared_ptr<WAICClient> newClient = make_shared<WAICClient>(initConnectionCommand.getPort(), initConnectionCommand.getAddress());

    insertNewClient(make_pair(newClient, clientID));

    shared_ptr<WAICResponse> response = make_shared<WAICDataResponse>("OK");

    return response;
}
