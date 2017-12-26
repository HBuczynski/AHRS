#include "CollectDataBuilder.h"
#include "CollectDataCommand.h"

using namespace std;
using namespace communication;

CollectDataBuilder::CollectDataBuilder()
{}

unique_ptr<Command> CollectDataBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<CollectDataCommand>();

    return move(command);
}
