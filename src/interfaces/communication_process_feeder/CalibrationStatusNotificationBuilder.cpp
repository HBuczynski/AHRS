#include "CalibrationStatusNotificationBuilder.h"
#include "CalibrationStatusNotification.h"

using namespace std;
using namespace communication;

CalibrationStatusNotificationBuilder::CalibrationStatusNotificationBuilder()
{}

CalibrationStatusNotificationBuilder::~CalibrationStatusNotificationBuilder()
{}

unique_ptr<FeederNotification> CalibrationStatusNotificationBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto ackType = static_cast<CalibrationStatus >(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<CalibrationStatusNotification>(ackType);

    return move(command);
}
