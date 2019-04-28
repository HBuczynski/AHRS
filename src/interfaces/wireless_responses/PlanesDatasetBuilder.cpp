#include "PlanesDatasetBuilder.h"
#include "PlanesDatasetResponse.h"

#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace utility;
using namespace communication;

PlanesDatasetBuilder::PlanesDatasetBuilder()
{}

PlanesDatasetBuilder::~PlanesDatasetBuilder()
{}

unique_ptr<Response> PlanesDatasetBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto dataSize = BytesConverter::fromVectorOfUINT8toUINT16(dataInBytes, Frame::DATA_SIZE_UINT16_POSITION) - 1;
    const auto planes = string(dataInBytes.begin()+Frame::INITIAL_DATA_POSITION, dataInBytes.begin() + Frame::INITIAL_DATA_POSITION + dataSize) ;

    auto command = make_unique<PlanesDatasetResponse>(planes);

    return move(command);
}
