#include "EndConnectionExecutor.h"

#include <waic_protocol/DataResponse.h>

using namespace std;
using namespace communication;

EndConnectionExecutor::EndConnectionExecutor(function<void (uint8_t) > callbackFunction, ClientThreadTCP *client)
    : removeClientFromList(callbackFunction),
      client_(client)
{

}

EndConnectionExecutor::~EndConnectionExecutor()
{
}

shared_ptr<Response> EndConnectionExecutor::execute(const vector<uint8_t> &vec, uint8_t clientID)
{
    removeClientFromList(clientID);
    client_->stopListen();

    // after this command socket is closed and response is not resent
    shared_ptr<Response> response;

    return response;
}
