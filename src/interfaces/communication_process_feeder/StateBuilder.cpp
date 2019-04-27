#include "StateBuilder.h"
#include "StateNotification.h"

using namespace std;
using namespace communication;

StateBuilder::StateBuilder()
{}

StateBuilder::~StateBuilder()
{}

unique_ptr<FeederNotification> StateBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = static_cast<FeederStateCode >(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<StateNotification>(code);

    return move(command);
}
