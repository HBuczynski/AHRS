#include "CommunicationStatusBuilder.h"
#include "CommunicationStatusNotification.h"

using namespace std;
using namespace communication;

CommunicationStatusBuilder::CommunicationStatusBuilder()
{ }

CommunicationStatusBuilder::~CommunicationStatusBuilder()
{ }

unique_ptr<UINotification> CommunicationStatusBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto mode = static_cast<UIExternalStateCode >(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<CommunicationStatusNotification>(mode);

    return move(command);
}
