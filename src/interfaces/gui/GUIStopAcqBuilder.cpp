#include "GUIStopAcqBuilder.h"
#include "GUIStopAcqResponse.h"

using namespace std;
using namespace communication;

GUIStopAcqBuilder::GUIStopAcqBuilder()
{}

GUIStopAcqBuilder::~GUIStopAcqBuilder()
{}

unique_ptr<GUIResponse> GUIStopAcqBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<GUIStopAcqResponse>();

    return move(command);
}
