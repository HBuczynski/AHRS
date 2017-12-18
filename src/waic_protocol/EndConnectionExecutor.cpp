#include "EndConnectionExecutor.h"
#include <waic_protocol/DataResponse.h>

using namespace std;
using namespace communication;

EndConnectionExecutor::EndConnectionExecutor(function<void (uint8_t) > callbackFunction)
    : removeClientFromList(callbackFunction)
{

}

EndConnectionExecutor::~EndConnectionExecutor()
{
}

shared_ptr<Response> EndConnectionExecutor::execute(const vector<uint8_t> &vec, uint8_t clientID)
{
    removeClientFromList(clientID);

    shared_ptr<Response> response = make_shared<DataResponse>("OK");

    return response;
}
