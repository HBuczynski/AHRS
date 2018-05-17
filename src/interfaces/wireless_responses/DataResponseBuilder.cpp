#include "DataResponseBuilder.h"
#include "DataResponse.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

DataResponseBuilder::DataResponseBuilder()
{}

DataResponseBuilder::~DataResponseBuilder()
{}

unique_ptr<Response> DataResponseBuilder::create(const vector<uint8_t> &dataInBytes)
{
    string planeName;
    planeName = BytesConverter::fromVectorOfUINT8toString(dataInBytes, INIT_DATA_POSITION);

    auto command = make_unique<DataResponse>(planeName);

    return move(command);
}
