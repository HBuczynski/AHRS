#include "UICommandFactory.h"
#include "UIChangeModeBuilder.h"

using namespace std;
using namespace communication;

UICommandFactory::UICommandFactory()
{

}

UICommandFactory::~UICommandFactory()
{

}

unique_ptr<UICommand> UICommandFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<UICommandType>(commandInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case UICommandType ::CHANGE_STATE :
            builder_ = make_unique<UIChangeModeBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
