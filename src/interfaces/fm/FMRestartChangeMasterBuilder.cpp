#include "FMRestartChangeMasterBuilder.h"
#include "FMRestartChangeMasterCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace communication;

unique_ptr<FMCommand> FMRestartChangeMasterBuilder::create(const std::vector<uint8_t> &dataInBytes)
{
    const auto systemState = utility::BytesConverter::fromVectorOfUINT8toString(dataInBytes, Frame::INITIAL_DATA_POSITION);

    auto command = make_unique<FMRestartChangeMasterCommand>(systemState);

    return move(command);
}

