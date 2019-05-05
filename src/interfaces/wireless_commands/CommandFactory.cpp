#include "CommandFactory.h"
#include "InitConnectionBuilder.h"
#include "SetPlaneBuilder.h"
#include "CollectDataBuilder.h"
#include "EndConnectionBuilder.h"
#include "RemovePlaneDataBuilder.h"
#include "StartAcquisitionBuilder.h"
#include "CalibrationStatusBuilder.h"
#include "CurrentStateBuilder.h"
#include "PerformBITsBuilder.h"
#include "CalibrateAccelerometerBuilder.h"
#include "CalibrateDataBuilder.h"
#include "CalibMagBuilder.h"
#include "BITSDataBuilder.h"

#include <stdexcept>
#include <iostream>

using namespace std;
using namespace communication;

CommandFactory::CommandFactory()
{}

CommandFactory::~CommandFactory()
{}

unique_ptr<Command> CommandFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<CommandType>(commandInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case CommandType::CALIBRATE_MAGNETOMETER :
            builder_ = make_unique<CalibMagBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::CALIBRATE_DATA :
            builder_ = make_unique<CalibrateDataBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::INIT_CONNECTION :
            builder_ = make_unique<InitConnectionBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::PERFORM_BIT :
            builder_ = make_unique<PerformBITsBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::CALIBRATE_ACCELEROMETER :
            builder_ = make_unique<CalibrateAccelerometerBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::REMOVE_PLANE_DATA :
            builder_ = make_unique<RemovePlaneDataBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::SET_PLANE_NAME :
            builder_ = make_unique<SetPlaneBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::COLLECT_DATA :
            builder_ = make_unique<CollectDataBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::CALIBRATION_STATUS :
            builder_ = make_unique<CalibrationStatusBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::START_ACQ :
            builder_ = make_unique<StartAcquisitionBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::CURRENT_STATE :
            builder_ = make_unique<CurrentStateBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::BITS_DATA :
            builder_ = make_unique<BITSDataBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::END_CONNECTION :
            builder_ = make_unique<EndConnectionBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
