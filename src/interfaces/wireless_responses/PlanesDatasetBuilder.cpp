#include "PlanesDatasetBuilder.h"
#include "PlanesDatasetResponse.h"

#include <config_reader/AircraftParameters.h>
#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

PlanesDatasetBuilder::PlanesDatasetBuilder()
{}

PlanesDatasetBuilder::~PlanesDatasetBuilder()
{}

unique_ptr<Response> PlanesDatasetBuilder::create(const vector<uint8_t> &dataInBytes)
{
    vector<AircraftParameters> dataset;
    uint16_t dataSize = BytesConverter::fromVectorOfUINT8toUINT16(dataInBytes, Frame::DATA_SIZE_UINT16_POSITION) - 1;

    if((dataSize % sizeof(AircraftParameters)) != 0)
    {
        throw invalid_argument("PlanesDatasetBuilder: wrong dataset");
    }

    uint16_t numberOfPlanes = dataSize / sizeof(AircraftParameters);
    uint16_t currentPosition = Frame::INITIAL_DATA_POSITION;

    AircraftParameters plane;

    for(uint16_t i = 0; i < numberOfPlanes; ++i)
    {
        BytesConverter::fromVectorOfUINT8toStruct(dataInBytes, currentPosition, plane);
        dataset.push_back(plane);

        currentPosition += sizeof(plane);
    }

    auto command = make_unique<PlanesDatasetResponse>(dataset);
    return move(command);
}
