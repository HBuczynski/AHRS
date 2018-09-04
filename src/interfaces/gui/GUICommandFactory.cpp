#include "GUICommandFactory.h"

#include "GUIWindowBuilder.h"

using namespace std;
using namespace communication;

GUICommandFactory::GUICommandFactory()
{}

GUICommandFactory::~GUICommandFactory()
{}

unique_ptr<GUICommand> GUICommandFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<GUICommandType>(commandInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case GUICommandType::CHANGE_WINDOW :
            builder_ = make_unique<GUIWindowBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
