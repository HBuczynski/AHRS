#include "HMInvalidConnectionBuilder.h"
#include "HMInvalidConnectionNotification.h"

using namespace std;
using namespace communication;

unique_ptr<HMNotification> HMInvalidConnectionBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = dataInBytes[Frame::INITIAL_DATA_POSITION];

    auto command = make_unique<HMInvalidConnectionNotification>(code);

    return move(command);
}
