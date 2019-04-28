#include "CalibrateAccelerometerResBuilder.h"
#include "CalibrateAccelerometerResponse.h"

using namespace std;
using namespace communication;

CalibrateAccelerometerResBuilder::CalibrateAccelerometerResBuilder()
{}

CalibrateAccelerometerResBuilder::~CalibrateAccelerometerResBuilder()
{}

unique_ptr<Response> CalibrateAccelerometerResBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto status = static_cast<AccelActionResponse>(dataInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<CalibrateAccelerometerResponse>(status);

    return move(command);
}

