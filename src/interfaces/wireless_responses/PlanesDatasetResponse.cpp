#include "PlanesDatasetResponse.h"
#include "ResponseVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

PlanesDatasetResponse::PlanesDatasetResponse(const string &dataset)
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
    BytesConverter::appendStringToVectorOfUINT8(dataset_, frame);

    return frame;
}

void PlanesDatasetResponse::initializeDataSize()
{
    dataSize_ = sizeof(responseType_);
    dataSize_ += sizeof(char)*dataset_.size();
}

string PlanesDatasetResponse::getName()
{
    return string("PlanesDatasetResponse");
}

void PlanesDatasetResponse::setDataset(const string &dataset)
{
    dataset_ = dataset;
}

string PlanesDatasetResponse::getDataset() const
{
    return dataset_;
}

void PlanesDatasetResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}
