#include "FeederCommandFactory.h"

#include "CalibrateMagnetometerBuilder.h"
#include "FeederWirelessWrapperBuilder.h"
#include "FeederCodeDemandBuilder.h"

using namespace std;
using namespace communication;

FeederCommandFactory::FeederCommandFactory()
{}

FeederCommandFactory::~FeederCommandFactory()
{}

std::unique_ptr<FeederCommand> FeederCommandFactory::createCommand(const std::vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<FeederCommandType >(commandInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case FeederCommandType::CALIBRATE_MAGNETOMETER_DEMAND :
            builder_ = make_unique<CalibrateMagnetometerBuilder>();
            return move(builder_->create(commandInBytes));

        case FeederCommandType::COMMAND_WRAPPER :
            builder_ = make_unique<FeederWirelessWrapperBuilder>();
            return move(builder_->create(commandInBytes));

        case FeederCommandType::FEEDER_CODE_DEMAND :
            builder_ = make_unique<FeederCodeDemandBuilder>();
            return move(builder_->create(commandInBytes));

        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
