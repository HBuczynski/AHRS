#include "PerformBITsBuilder.h"
#include "PerformBITsCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

PerformBITsBuilder::PerformBITsBuilder()
{}

PerformBITsBuilder::~PerformBITsBuilder()
{}

std::unique_ptr<Command> PerformBITsBuilder::create(const std::vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<PerformBITsCommand>();

    return move(command);
}
