#include "PlanesDatasetResponse.h"
#include "ResponseVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

PlanesDatasetResponse::PlanesDatasetResponse(const vector<config::AircraftParameters> &dataset)
    : Response(10, ResponseType::PLANES_DATASET),
      dataset_(dataset)
{ }

PlanesDatasetResponse::~PlanesDatasetResponse()
{ }

vector<uint8_t> PlanesDatasetResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    for(const auto& plane : dataset_)
    {
        const auto serializedPlane = BytesConverter::appendStructToVectorOfUINT8(plane);
        frame.insert(frame.end(), serializedPlane.begin(), serializedPlane.end());
    }

    return frame;
}

void PlanesDatasetResponse::initializeDataSize()
{
    dataSize_ = sizeof(responseType_);

    for(const auto& plane : dataset_)
    {
        dataSize_ += sizeof(plane);
    }
}

string PlanesDatasetResponse::getName()
{
    return string("PlanesDatasetResponse");
}

void PlanesDatasetResponse::setDataset(const vector<config::AircraftParameters> &dataset)
{
    dataset_ = dataset;
}

const vector<config::AircraftParameters> &PlanesDatasetResponse::getDataset() const
{
    return dataset_;
}

void PlanesDatasetResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}
