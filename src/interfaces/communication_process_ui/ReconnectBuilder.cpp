#include "ReconnectBuilder.h"
#include "ReconnectCommand.h"

using namespace std;
using namespace communication;

ReconnectBuilder::ReconnectBuilder()
{}

ReconnectBuilder::~ReconnectBuilder()
{}

unique_ptr<UICommand> ReconnectBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<ReconnectCommand>();

    return move(command);;
}
