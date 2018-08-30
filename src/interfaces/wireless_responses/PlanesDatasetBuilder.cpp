#include "PlanesDatasetBuilder.h"
#include "PlanesDatasetResponse.h"

#include <config_reader/AircraftParameters.h>
#include <utility/BytesConverter.h>

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
    uint16_t currentPosition = Frame::INITIAL_DATA_POSITION;

    while (currentPosition < dataInBytes.size())
    {
        const auto  plane = BytesConverter::fromVectorOfUINT8toString(dataInBytes, currentPosition);
        //dataset.push_back(plane);

        currentPosition += sizeof(plane);
    }

    auto command = make_unique<PlanesDatasetResponse>(dataset);
    return move(command);
}
