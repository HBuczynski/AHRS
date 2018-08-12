#include "CalibrationStatusBuilder.h"
#include "CalibrationStatusCommand.h"

using namespace std;
using namespace communication;

CalibrationStatusBuilder::CalibrationStatusBuilder()
{}

CalibrationStatusBuilder::~CalibrationStatusBuilder()
{}

unique_ptr<Command> CalibrationStatusBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<CalibrationStatusCommand>();

    return move(command);
}
