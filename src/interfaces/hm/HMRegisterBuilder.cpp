#include "HMRegisterBuilder.h"
#include "HMRegisterNotification.h"

using namespace std;
using namespace communication;

unique_ptr<HMNotification> HMRegisterBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = static_cast<HMNodes>(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<HMRegisterNotification>(code);

    return move(command);
}

