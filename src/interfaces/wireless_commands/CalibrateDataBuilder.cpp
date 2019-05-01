#include "CalibrateDataBuilder.h"
#include "CalibrateDataCommand.h"

using namespace std;
using namespace communication;

CalibrateDataBuilder::CalibrateDataBuilder()
{}

CalibrateDataBuilder::~CalibrateDataBuilder()
{}

unique_ptr<Command> CalibrateDataBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<CalibrateDataCommand>();

    return move(command);
}
