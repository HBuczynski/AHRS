#include "HMCommandFactory.h"

#include "HMErrorCommandBuilder.h"
#include "HMInvalidConnectionCommandBuilder.h"

using namespace std;
using namespace communication;

HMCommandFactory::HMCommandFactory()
{}

HMCommandFactory::~HMCommandFactory()
{}

unique_ptr<HMCommand> HMCommandFactory::createCommand(const std::vector<uint8_t> &notificationInBytes)
{
    const auto type = static_cast<HMCommandType >(notificationInBytes[Frame::NOTIFICATION_TYPE_POSITION]);

    switch (type)
    {
        case HMCommandType::COMMAND_ERROR:
            builder_ = make_unique<HMErrorCommandBuilder>();
            return move(builder_->create(notificationInBytes));

        case HMCommandType::INVALID_CONNECTION_COMM:
            builder_ = make_unique<HMInvalidConnectionCommandBuilder>();
            return move(builder_->create(notificationInBytes));

        default:
            throw invalid_argument("Received command does not register in factory.");
    }
}
