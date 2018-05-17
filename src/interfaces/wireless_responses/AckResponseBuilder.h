#ifndef AHRS_ACKRESPONSEBUILDER_H
#define AHRS_ACKRESPONSEBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class AckResponseBuilder final : public ResponseBuilder
    {
    public:
        AckResponseBuilder();
        ~AckResponseBuilder();

        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}
#endif
