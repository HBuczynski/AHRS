#include "MeasuringDataFactory.h"

#include "ImuDataBuilder.h"
#include "GpsDataBuilder.h"
#include "FeedertDataBuilder.h"

#include <stdexcept>

using namespace std;
using namespace communication;

MeasuringDataFactory::MeasuringDataFactory()
{}

MeasuringDataFactory::~MeasuringDataFactory()
{}

unique_ptr<MeasuringData> MeasuringDataFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<MeasuringType>(commandInBytes[Frame::MEASUREMENT_DATA_TYPE_POSITION]);

    switch (type)
    {
        case MeasuringType::IMU :
            builder_ = make_unique<ImuDataBuilder>();
            return move(builder_->create(commandInBytes));
        case MeasuringType::GPS :
            builder_ = make_unique<GpsDataBuilder>();
            return move(builder_->create(commandInBytes));
        case MeasuringType::FLIGHT_DATA :
            builder_ = make_unique<FeedertDataBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");
    }
}
