#include "InitConnectionBuilder.h"
#include "InitConnectionCommand.h"

using namespace std;
using namespace communication;

InitConnectionBuilder::InitConnectionBuilder()
{

}

std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes)
{
    uint16_t port;
    std::string address;

    //TO DO

    unique_ptr<Command> command = make_unique<InitConnectionCommand>(port, address);

    return move(command);
}
