#include "GUIPlaneBuilder.h"
#include "GUIPlaneResponse.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

GUIPlaneBuilder::GUIPlaneBuilder()
{}

GUIPlaneBuilder::~GUIPlaneBuilder()
{}

unique_ptr<GUIResponse> GUIPlaneBuilder::create(const vector<uint8_t> &commandInBytes)
{
    uint8_t currentPosition = Frame::INITIAL_DATA_POSITION;
    string planeName = BytesConverter::fromVectorOfUINT8toString(commandInBytes, currentPosition);

    auto command = make_unique<GUIPlaneResponse>(planeName);

    return move(command);
}