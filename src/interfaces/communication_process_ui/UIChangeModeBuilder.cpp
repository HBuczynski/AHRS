#include "UIChangeModeBuilder.h"
#include "UIChangeModeCommand.h"

using namespace std;
using namespace communication;

UIChangeModeBuilder::UIChangeModeBuilder()
{

}

UIChangeModeBuilder::~UIChangeModeBuilder()
{

}

unique_ptr<UICommand> UIChangeModeBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto mode = static_cast<CommunicationProcessMode>(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<UIChangeModeCommand>(mode);

    return move(command);
}
