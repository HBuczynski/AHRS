#include "DbHashBuilder.h"
#include "DbHashNotification.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

DbHashBuilder::DbHashBuilder()
{}

DbHashBuilder::~DbHashBuilder()
{}

unique_ptr<FeederNotification> DbHashBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto hash = BytesConverter::fromVectorOfUINT8toUINT32(dataInBytes, Frame::INITIAL_DATA_POSITION);

    auto command = make_unique<DbHashNotification>(hash);

    return move(command);
}
