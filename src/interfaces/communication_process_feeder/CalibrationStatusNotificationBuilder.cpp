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
    const auto ackType = static_cast<CalibrationStatus >(commandInBytes[INIT_DATA_POSITION_IN_FRAME]);
    auto command = make_unique<CalibrationStatusNotification>(ackType);

    return move(command);
}
