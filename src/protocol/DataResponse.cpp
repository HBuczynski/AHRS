#include "DataResponse.h"
#include "ResponseVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
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

    BytesConverter::appendStringToVectorOfUINT8(data_, frame);

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
    dataSize += data_.size() + sizeof(END_STRING_IN_FRAME);

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
