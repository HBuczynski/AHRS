#include "DataResponse.h"

using namespace std;
using namespace communication;

DataResponse::DataResponse(string dataIn)
    : Response(10, ResponseType::DATA),
      data_(dataIn)
{}

DataResponse::~DataResponse()
{}

vector<uint8_t> DataResponse::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(responseType));

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