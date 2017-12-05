#include "WAICEndConnectionHandler.h"
#include <waic_protocol/WAICDataResponse.h>

using namespace std;
using namespace communication;

WAICEndConnectionHandler::WAICEndConnectionHandler(function<void (uint8_t) > callbackFunction)
    : removeClientFromList(callbackFunction)
{

}

WAICEndConnectionHandler::~WAICEndConnectionHandler()
{
}

shared_ptr<WAICResponse> WAICEndConnectionHandler::handler(const vector<uint8_t> &vec, uint8_t clientID)
{
    removeClientFromList(clientID);

    shared_ptr<WAICResponse> response = make_shared<WAICDataResponse>("OK");

    return response;
}
