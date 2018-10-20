#include "BITsResponseBuilder.h"
#include "BITsResponse.h"

using namespace std;
using namespace communication;

BITsResponseBuilder::BITsResponseBuilder()
{}

BITsResponseBuilder::~BITsResponseBuilder()
{}

unique_ptr<Response> BITsResponseBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto state = dataInBytes[Frame::INITIAL_DATA_POSITION];
    const auto mode = static_cast<config::UICommunicationMode >(dataInBytes[Frame::INITIAL_DATA_POSITION+1]);

    auto command = make_unique<BITsResponse>(state, mode);

    return move(command);
}