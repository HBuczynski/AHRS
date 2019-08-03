#include "ReceivingDataBuilder.h"
#include "ReceivingDataNotification.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

ReceivingDataBuilder::ReceivingDataBuilder()
{ }

ReceivingDataBuilder::~ReceivingDataBuilder()
{ }

unique_ptr<UINotification> ReceivingDataBuilder::create(const vector<uint8_t> &commandInBytes)
{
    vector<uint8_t> data;
    uint16_t dataSize = BytesConverter::fromVectorOfUINT8toUINT16(commandInBytes, Frame::DATA_SIZE_UINT16_POSITION) - 2;

    uint8_t commMode = commandInBytes[Frame::INITIAL_DATA_POSITION];
    data.insert(data.begin(), commandInBytes.begin()+Frame::INITIAL_DATA_POSITION + 1, commandInBytes.begin() + Frame::INITIAL_DATA_POSITION + dataSize +1);

    auto command = make_unique<ReceivingDataNotification>(commMode, data);

    return move(command);
}
