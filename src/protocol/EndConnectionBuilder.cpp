#include "EndConnectionBuilder.h"
#include "EndConnectionCommand.h"

using namespace std;
using namespace communication;

EndConnectionBuilder::EndConnectionBuilder()
{}

unique_ptr<Command> EndConnectionBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<EndConnectionCommand>();

    return move(command);
}
