#ifndef AHRS_BITSRESPONSEBUILDER_H
#define AHRS_BITSRESPONSEBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class BITsResponseBuilder final : public ResponseBuilder
    {
    public:
        BITsResponseBuilder();
        ~BITsResponseBuilder();

        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif //AHRS_BITSRESPONSEBUILDER_H
