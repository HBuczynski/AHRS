#include "UICommandFactory.h"
#include "UIChangeModeBuilder.h"
#include "ShutdownBuilder.h"
#include "ReconnectBuilder.h"
#include "SendingDataBuilder.h"
#include "DatabaseHashBuilder.h"

using namespace std;
using namespace communication;

UICommandFactory::UICommandFactory()
{}

UICommandFactory::~UICommandFactory()
{}

unique_ptr<UICommand> UICommandFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<UICommandType>(commandInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case UICommandType ::CHANGE_STATE :
            builder_ = make_unique<UIChangeModeBuilder>();
            return move(builder_->create(commandInBytes));
        case UICommandType ::SHUTDOWN :
            builder_ = make_unique<ShutdownBuilder>();
            return move(builder_->create(commandInBytes));
        case UICommandType ::RECONNECT :
            builder_ = make_unique<ReconnectBuilder>();
            return move(builder_->create(commandInBytes));
        case UICommandType ::SEND_FRAME :
            builder_ = make_unique<SendingDataBuilder>();
            return move(builder_->create(commandInBytes));
        case UICommandType ::DATABASE_HASH :
            builder_ = make_unique<DatabaseHashBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
