#include "GUIWirelessComWrapperBuilder.h"
#include "GUIWirelessComWrapperResponse.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

GUIWirelessComWrapperBuilder::GUIWirelessComWrapperBuilder()
{}

GUIWirelessComWrapperBuilder::~GUIWirelessComWrapperBuilder()
{}

unique_ptr<GUIResponse> GUIWirelessComWrapperBuilder::create(const vector<uint8_t> &commandInBytes)
{
    vector<uint8_t> data;
    uint16_t dataSize = BytesConverter::fromVectorOfUINT8toUINT16(commandInBytes, Frame::DATA_SIZE_UINT16_POSITION) - 1;

    config::UICommunicationMode mode = static_cast<config::UICommunicationMode>(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    data.insert(data.begin(), commandInBytes.begin()+Frame::INITIAL_DATA_POSITION + 1, commandInBytes.begin() + Frame::INITIAL_DATA_POSITION + dataSize +1);
    auto command = make_unique<GUIWirelessComWrapperResponse>(mode, data);

    return move(command);
}
