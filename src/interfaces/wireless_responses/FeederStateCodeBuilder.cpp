#include "FeederStateCodeBuilder.h"
#include "FeederStateCodeResponse.h"

using namespace std;
using namespace communication;

FeederStateCodeBuilder::FeederStateCodeBuilder()
{}

FeederStateCodeBuilder::~FeederStateCodeBuilder()
{}

unique_ptr<Response> FeederStateCodeBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = static_cast<FeederStateCode >(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<FeederStateCodeResponse>(code);

    return move(command);
}
