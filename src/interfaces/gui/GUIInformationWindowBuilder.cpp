#include "GUIInformationWindowBuilder.h"
#include "GUIInformationWindowCommand.h"

using namespace std;
using namespace communication;

GUIInformationWindowBuilder::GUIInformationWindowBuilder()
{}

GUIInformationWindowBuilder::~GUIInformationWindowBuilder()
{}

unique_ptr<GUICommand> GUIInformationWindowBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto masterConnection =commandInBytes[Frame::INITIAL_DATA_POSITION];
    const auto redundantConnection =commandInBytes[Frame::INITIAL_DATA_POSITION + 1];
    const auto bitsPerformance =commandInBytes[Frame::INITIAL_DATA_POSITION + 2];

    auto command = make_unique<GUIInformationWindowCommand>(masterConnection, redundantConnection, bitsPerformance);

    return move(command);
}