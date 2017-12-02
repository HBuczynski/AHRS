#include "WAICDataResponse.h"

using namespace std;
using namespace communication;

WAICDataResponse::WAICDataResponse(string dataIn)
    : WAICResponse(10, WAICResponseType::DATA),
      data(dataIn)
{

}

WAICDataResponse::WAICDataResponse(const vector<uint8_t> &frameBytes)
        : WAICResponse(10, WAICResponseType::DATA)
{
}

WAICDataResponse::~WAICDataResponse()
{
}

vector<uint8_t> WAICDataResponse::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(responseType));



    return frame;
}

string WAICDataResponse::getName()
{
    return string("DataResponse");
}
