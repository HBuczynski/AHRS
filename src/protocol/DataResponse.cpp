#include "DataResponse.h"

using namespace std;
using namespace communication;

DataResponse::DataResponse(string dataIn)
    : Response(10, ResponseType::DATA),
      data(dataIn)
{

}

DataResponse::DataResponse(const vector<uint8_t> &frameBytes)
        : Response(10, ResponseType::DATA)
{
}

DataResponse::~DataResponse()
{
}

vector<uint8_t> DataResponse::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(responseType));



    return frame;
}

string DataResponse::getName()
{
    return string("DataResponse");
}
