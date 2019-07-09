#include "FMCommandFactory.h"

#include "FMResetCommunicationProcessBuilder.h"

using namespace std;
using namespace communication;

FMCommandFactory::FMCommandFactory()
{}

FMCommandFactory::~FMCommandFactory()
{}

unique_ptr<FMCommand> FMCommandFactory::createCommand(const std::vector<uint8_t> &notificationInBytes)
{
    const auto type = static_cast<FMCommandType >(notificationInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case FMCommandType::RESET_COMMUNICATION_PROCESS:
            builder_ = make_unique<FMResetCommunicationProcessBuilder>();
            return move(builder_->create(notificationInBytes));

        default:
            throw invalid_argument("Received command does not register in factory.");
    }
}
