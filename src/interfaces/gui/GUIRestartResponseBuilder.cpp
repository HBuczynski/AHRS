#include "GUIRestartResponseBuilder.h"
#include "GUIRestartResponse.h"

using namespace std;
using namespace communication;

GUIRestartResponseBuilder::GUIRestartResponseBuilder()
{}

GUIRestartResponseBuilder::~GUIRestartResponseBuilder()
{}

unique_ptr<GUIResponse> GUIRestartResponseBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<GUIRestartResponse>();

    return move(command);
}
