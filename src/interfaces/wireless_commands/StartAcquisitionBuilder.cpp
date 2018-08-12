#include "StartAcquisitionBuilder.h"
#include "StartAcquisitionCommand.h"

using namespace std;
using namespace communication;

StartAcquisitionBuilder::StartAcquisitionBuilder()
{}

StartAcquisitionBuilder::~StartAcquisitionBuilder()
{}

unique_ptr<Command> StartAcquisitionBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<StartAcquisitionCommand>();

    return move(command);
}
