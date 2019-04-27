#include "CurrentStateBuilder.h"
#include "CurrentStateResponse.h"

using namespace std;
using namespace communication;

CurrentStateBuilder::CurrentStateBuilder()
{}

CurrentStateBuilder::~CurrentStateBuilder()
{}

unique_ptr<Response> CurrentStateBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = static_cast<FeederStateCode >(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<CurrentStateResponse>(code);

    return move(command);
}