#include "DataResponse.h"
#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

DataResponse::DataResponse(const string& data)
    : Response(10, ResponseType::DATA),
      data_(data)
{}

DataResponse::~DataResponse()
{}

vector<uint8_t> DataResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(responseType_));

    vector<uint8_t > name(data_.begin(), data_.end());
    frame.insert(frame.end(), name.begin(), name.end());

    return frame;
}

string DataResponse::getName()
{
    return string("DataResponse");
}

const string& DataResponse::getData() const
{
    return data_;
}

void DataResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += data_.size();

    setDataSize(dataSize);
}

void DataResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}

void DataResponse::setData(const string &data)
{
    data_ = data;
}
