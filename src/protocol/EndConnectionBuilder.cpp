#include "EndConnectionBuilder.h"

using namespace std;
using namespace communication;

EndConnectionBuilder::EndConnectionBuilder()
{}

unique_ptr<Command> EndConnectionBuilder::create(const vector<uint8_t> &commandInBytes)
{
    return unique_ptr<Command>();
}
