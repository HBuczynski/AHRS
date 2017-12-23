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

shared_ptr<Command> CommandFactory::createCommand(vector<uint8_t> commandInBytes)
{
    CommandType type = static_cast<CommandType>(commandInBytes[5]); // coonst, zmienic 5
    shared_ptr<Command> command;

    switch(type)
    {
        case CommandType::INIT_CONNECTION :
            builder_ = make_unique<InitConnectionBuilder>();
            command = builder_->create(commandInBytes);
            break; // zamiast break to return
        case CommandType::CALIBRATE_MAGNETOMETER :
            break;
        case CommandType::COLLECT_DATA :
            break;
        case CommandType::END_CONNECTION :
            break;
        default:
            throw invalid_argument("Received command does not register in factory.");
    }

    return command;
}
