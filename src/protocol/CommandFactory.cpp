#include "CommandFactory.h"
#include "InitConnectionBuilder.h"
#include "CalibrateMagnetometerBuilder.h"
#include "SetPlaneMagnetometerBuilder.h"
#include "CollectDataBuilder.h"
#include "EndConnectionBuilder.h"

#include <stdexcept>

using namespace std;
using namespace communication;

CommandFactory::CommandFactory()
{}

CommandFactory::~CommandFactory()
{}

unique_ptr<Command> CommandFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<CommandType>(commandInBytes[COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case CommandType::INIT_CONNECTION :
            builder_ = make_unique<InitConnectionBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::CALIBRATE_MAGNETOMETER :
            builder_ = make_unique<CalibrateMagnetometerBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::SET_PLANE_MAGNETOMETER_DATA :
            builder_ = make_unique<SetPlaneMagnetometerBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::COLLECT_DATA :
            builder_ = make_unique<CollectDataBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::END_CONNECTION :
            builder_ = make_unique<EndConnectionBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
