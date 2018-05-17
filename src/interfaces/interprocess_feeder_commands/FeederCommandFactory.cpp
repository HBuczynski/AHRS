#include "FeederCommandFactory.h"

using namespace std;
using namespace communication;

FeederCommandFactory::FeederCommandFactory()
{}

FeederCommandFactory::~FeederCommandFactory()
{}

std::unique_ptr<FeederCommand> FeederCommandFactory::createCommand(const std::vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<FeederCommandType >(commandInBytes[COMMAND_TYPE_POSITION]);

    switch (type)
    {
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
