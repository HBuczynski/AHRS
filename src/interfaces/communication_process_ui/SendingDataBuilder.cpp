#include "SendingDataBuilder.h"
#include "SendingDataCommand.h"
#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;


SendingDataBuilder::SendingDataBuilder()
{}

SendingDataBuilder::~SendingDataBuilder()
{}

unique_ptr<UICommand> SendingDataBuilder::create(const vector<uint8_t> &commandInBytes)
{
    vector<uint8_t> data;
    uint16_t dataSize = BytesConverter::fromVectorOfUINT8toUINT16(commandInBytes, Frame::DATA_SIZE_UINT16_POSITION);;

    data.insert(data.begin(), commandInBytes.begin()+Frame::INITIAL_DATA_POSITION, commandInBytes.begin() + dataSize);
    auto command = make_unique<SendingDataCommand>(data);

    return move(command);
}
