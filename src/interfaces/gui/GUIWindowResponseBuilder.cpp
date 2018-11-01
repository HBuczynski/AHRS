#include "GUIWindowResponseBuilder.h"
#include "GUIWindowResponse.h"

using namespace std;
using namespace communication;

GUIWindowResponseBuilder::GUIWindowResponseBuilder()
{}

GUIWindowResponseBuilder::~GUIWindowResponseBuilder()
{}

unique_ptr<GUIResponse> GUIWindowResponseBuilder::create(const vector<uint8_t> &commandInBytes)
{
    uint8_t currentPosition = Frame::INITIAL_DATA_POSITION;
    const auto window = static_cast<PagesType >(commandInBytes[currentPosition]);
    auto command = make_unique<GUIWindowResponse>(window);

    return move(command);
}
