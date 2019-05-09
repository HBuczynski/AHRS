#include "DatabaseHashBuilder.h"
#include "DatabaseHashCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

DatabaseHashBuilder::DatabaseHashBuilder()
{}

DatabaseHashBuilder::~DatabaseHashBuilder()
{}

unique_ptr<UICommand> DatabaseHashBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto position = Frame::INITIAL_DATA_POSITION;
    auto hash = BytesConverter::fromVectorOfUINT8toUINT32(commandInBytes, position);
    position += sizeof(hash);

    auto dbName = BytesConverter::fromVectorOfUINT8toString(commandInBytes, position);

    auto command = make_unique<DatabaseHashCommand>(hash, dbName);

    return move(command);;
}
