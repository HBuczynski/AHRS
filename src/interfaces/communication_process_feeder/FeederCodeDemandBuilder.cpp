#include "FeederCodeDemandBuilder.h"
#include "FeederCodeDemandCommand.h"

using namespace std;
using namespace communication;

FeederCodeDemandBuilder::FeederCodeDemandBuilder()
{}

FeederCodeDemandBuilder::~FeederCodeDemandBuilder()
{}

unique_ptr<FeederCommand> FeederCodeDemandBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = static_cast<FeederStateCode >(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<FeederCodeDemandCommand>(code);

    return move(command);
}
