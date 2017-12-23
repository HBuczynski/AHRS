#include "CommandFactory.h"
#include "InitConnectionBuilder.h"

#include <stdexcept>

using namespace std;
using namespace communication;

CommandFactory::CommandFactory()
{
}

CommandFactory::~CommandFactory()
{
}

unique_ptr<Command> CommandFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<CommandType>(commandInBytes[COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case CommandType::INIT_CONNECTION :
            builder_ = make_unique<InitConnectionBuilder>();
            return move(builder_->create(commandInBytes));

        case CommandType::CALIBRATE_MAGNETOMETER :
            break;
        case CommandType::COLLECT_DATA :
            break;
        case CommandType::END_CONNECTION :
            break;
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
