#include "CommunicationStatusBuilder.h"
#include "CommunicationStatusNotification.h"

using namespace std;
using namespace communication;

CommunicationStatusBuilder::CommunicationStatusBuilder()
{}

CommunicationStatusBuilder::~CommunicationStatusBuilder()
{}

unique_ptr<UINotification> CommunicationStatusBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto mode = static_cast<UIExternalComCode >(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    const auto processNumber = commandInBytes[Frame::INITIAL_DATA_POSITION+1];
    auto command = make_unique<CommunicationStatusNotification>(mode, processNumber);

    return move(command);
}
