#include "HMHeartbeatBuilder.h"
#include "HMHeartbeatNotification.h"

using namespace std;
using namespace communication;

unique_ptr<HMNotification> HMHeartbeatBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = static_cast<HMNodes>(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<HMHeartbeatNotification>(code);

    return move(command);
}
