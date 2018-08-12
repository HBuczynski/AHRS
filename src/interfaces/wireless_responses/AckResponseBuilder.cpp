#include "AckResponseBuilder.h"
#include "AckResponse.h"

using namespace std;
using namespace communication;

AckResponseBuilder::AckResponseBuilder()
{}

AckResponseBuilder::~AckResponseBuilder()
{}

unique_ptr<Response> AckResponseBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto ackType = static_cast<AckType>(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<AckResponse>(ackType);

    return move(command);
}
