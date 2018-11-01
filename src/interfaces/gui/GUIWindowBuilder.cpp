#include "GUIWindowBuilder.h"
#include "GUIWindowCommand.h"

using namespace std;
using namespace communication;

GUIWindowBuilder::GUIWindowBuilder()
{}

GUIWindowBuilder::~GUIWindowBuilder()
{}

unique_ptr<GUICommand> GUIWindowBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto windowType = static_cast<PagesType>(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<GUIWindowCommand>(windowType);

    return move(command);
}