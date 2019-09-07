#include "GUIShutdownResponseBuilder.h"
#include "GUIShutdownResponse.h"

using namespace std;
using namespace communication;

GUIShutdownResponseBuilder::GUIShutdownResponseBuilder()
{}

GUIShutdownResponseBuilder::~GUIShutdownResponseBuilder()
{}

unique_ptr<GUIResponse> GUIShutdownResponseBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<GUIShutdownResponse>();

    return move(command);
}
