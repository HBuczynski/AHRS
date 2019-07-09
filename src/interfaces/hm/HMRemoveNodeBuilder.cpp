#include "HMRemoveNodeBuilder.h"
#include "HMRemoveNodeNotification.h"

using namespace std;
using namespace communication;

unique_ptr<HMNotification> HMRemoveNodeBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = static_cast<HMNodes>(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<HMRemoveNodeNotification>(code);

    return move(command);
}
