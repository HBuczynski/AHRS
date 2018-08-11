#ifndef AHRS_CALIBRATINGSTATUSBUILDER_H
#define AHRS_CALIBRATINGSTATUSBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class CalibratingStatusBuilder final : public ResponseBuilder
    {
    public:
        CalibratingStatusBuilder();
        ~CalibratingStatusBuilder();

        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif