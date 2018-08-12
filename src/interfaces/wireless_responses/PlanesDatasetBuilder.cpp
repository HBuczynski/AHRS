#include "PlanesDatasetBuilder.h"
#include "PlanesDatasetResponse.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

PlanesDatasetBuilder::PlanesDatasetBuilder()
{}

PlanesDatasetBuilder::~PlanesDatasetBuilder()
{}

unique_ptr<Response> PlanesDatasetBuilder::create(const vector<uint8_t> &dataInBytes)
{
    vector<string> dataset;
    uint16_t currentPosition = INIT_DATA_POSITION;

    while (currentPosition <= dataInBytes.size())
    {
        string plane = BytesConverter::fromVectorOfUINT8toString(dataInBytes, currentPosition);
        dataset.push_back(plane);

        currentPosition = plane.size() + sizeof(END_STRING_IN_FRAME);
    }

    auto command = make_unique<PlanesDatasetResponse>(dataset);

    return move(command);
}
