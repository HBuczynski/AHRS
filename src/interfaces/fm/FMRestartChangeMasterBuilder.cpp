#include "FMRestartChangeMasterBuilder.h"
#include "FMRestartChangeMasterCommand.h"

using namespace std;
using namespace communication;

unique_ptr<FMCommand> FMRestartChangeMasterBuilder::create(const std::vector<uint8_t> &dataInBytes)
{
    auto command = make_unique<FMRestartChangeMasterCommand>();

    return move(command);
}

