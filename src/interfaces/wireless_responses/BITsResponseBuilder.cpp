#include "BITsResponseBuilder.h"
#include "BITsResponse.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

BITsResponseBuilder::BITsResponseBuilder()
{}

BITsResponseBuilder::~BITsResponseBuilder()
{}

unique_ptr<Response> BITsResponseBuilder::create(const vector<uint8_t> &dataInBytes)
{
    int16_t position = Frame::INITIAL_DATA_POSITION;

    BitsInformation bitsInformation;
    BytesConverter::fromVectorOfUINT8toStruct(dataInBytes, position, bitsInformation);

    auto command = make_unique<BITsResponse>(bitsInformation);

    return move(command);
}
