#include "CalibratingStatusBuilder.h"
#include "CalibratingStatusResponse.h"

using namespace std;
using namespace communication;

CalibratingStatusBuilder::CalibratingStatusBuilder()
{}

CalibratingStatusBuilder::~CalibratingStatusBuilder()
{}

unique_ptr<Response> CalibratingStatusBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto ackType = static_cast<CalibrationStatus >(dataInBytes[INIT_DATA_POSITION]);
    auto command = make_unique<CalibratingStatusResponse>(ackType);

    return move(command);
}
