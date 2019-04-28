#ifndef CALIBRATEACCELEROMETERRESBUILDER_H
#define CALIBRATEACCELEROMETERRESBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class CalibrateAccelerometerResBuilder final : public ResponseBuilder
    {
    public:
        CalibrateAccelerometerResBuilder();
        ~CalibrateAccelerometerResBuilder();

        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // CALIBRATEACCELEROMETERRESBUILDER_H
