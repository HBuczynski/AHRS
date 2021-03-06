#include "RemovePlaneDataBuilder.h"

#include "RemovePlaneDataCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

RemovePlaneDataBuilder::RemovePlaneDataBuilder()
{}

RemovePlaneDataBuilder::~RemovePlaneDataBuilder()
{}

unique_ptr<Command> RemovePlaneDataBuilder::create(const vector<uint8_t> &commandInBytes)
{
    uint8_t currentPosition = Frame::INITIAL_DATA_POSITION;
    string planeName = BytesConverter::fromVectorOfUINT8toString(commandInBytes, currentPosition);

    auto command = make_unique<RemovePlaneDataCommand>(planeName);

    return move(command);
}
