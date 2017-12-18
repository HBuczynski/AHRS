#include "InitConnectionBuilder.h"
#include "InitConnectionCommand.h"

using namespace std;
using namespace communication;

InitConnectionBuilder::InitConnectionBuilder()
{

}

shared_ptr<Command> InitConnectionBuilder::create(vector<uint8_t> commandInBytes)
{
    uint16_t port;
    std::string address;

    //TO DO

    shared_ptr<Command> command(new InitConnectionCommand(port, address));

    return command;
}
