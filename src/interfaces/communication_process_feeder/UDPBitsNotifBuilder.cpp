#include "UDPBitsNotifBuilder.h"
#include "UDPBitsNotification.h"

using namespace std;
using namespace communication;

UDPBitsNotifBuilder::UDPBitsNotifBuilder()
{}

UDPBitsNotifBuilder::~UDPBitsNotifBuilder()
{}

unique_ptr<FeederNotification> UDPBitsNotifBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = static_cast<BITS_ACTION >(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<UDPBitsNotification>(code);

    return move(command);
}
