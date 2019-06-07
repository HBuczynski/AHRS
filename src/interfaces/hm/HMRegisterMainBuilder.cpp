#include "HMRegisterMainBuilder.h"
#include "HMRegisterMainNotification.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

unique_ptr<HMNotification> HMRegisterMainBuilder::create(const vector<uint8_t> &dataInBytes)
{
    uint32_t position = Frame::INITIAL_DATA_POSITION;

    const auto code = static_cast<HMNodes>(dataInBytes[position]);
    position += sizeof(code);

    string name = BytesConverter::fromVectorOfUINT8toString(dataInBytes, position);
    position += name.size() + 1;

    uint32_t size = BytesConverter::fromVectorOfUINT8toUINT32(dataInBytes, position);
    auto command = make_unique<HMRegisterMainNotification>(code, name, size);

    return move(command);
}
