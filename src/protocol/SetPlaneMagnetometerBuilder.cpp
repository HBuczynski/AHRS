#include "SetPlaneMagnetometerBuilder.h"

using namespace std;
using namespace communication;

SetPlaneMagnetometerBuilder::SetPlaneMagnetometerBuilder()
{}

unique_ptr<Command> SetPlaneMagnetometerBuilder::create(const vector<uint8_t> &commandInBytes)
{


    return std::unique_ptr<communication::Command>();
}
