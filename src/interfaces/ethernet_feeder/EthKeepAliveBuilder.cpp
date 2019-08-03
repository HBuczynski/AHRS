#include "EthKeepAliveBuilder.h"
#include "EthKeepAliveCommand.h"

using namespace std;
using namespace communication;

EthKeepAliveBuilder::EthKeepAliveBuilder()
{}

EthKeepAliveBuilder::~EthKeepAliveBuilder()
{}

unique_ptr<EthFeederCommand> EthKeepAliveBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<EthKeepAliveCommand>();

    return move(command);
}

