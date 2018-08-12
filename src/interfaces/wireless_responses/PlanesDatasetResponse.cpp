#include "PlanesDatasetResponse.h"
#include "ResponseVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

PlanesDatasetResponse::PlanesDatasetResponse(const vector<string> &dataset)
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
        BytesConverter::appendStringToVectorOfUINT8(plane, frame);
    }

    return frame;
}

void PlanesDatasetResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);

    for(const auto& plane : dataset_)
    {
        dataSize += plane.size() + sizeof(END_STRING_IN_FRAME);
    }
}

string PlanesDatasetResponse::getName()
{
    return string("PlanesDatasetResponse");
}

void PlanesDatasetResponse::setDataset(const vector<string> &dataset)
{
    dataset_ = dataset;
}

const vector<string> &PlanesDatasetResponse::getDataset() const
{
    return dataset_;
}

void PlanesDatasetResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}
