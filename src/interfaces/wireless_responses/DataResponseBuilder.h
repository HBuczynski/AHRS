#ifndef AHRS_DATARESPONSEBUILDER_H
#define AHRS_DATARESPONSEBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class DataResponseBuilder final : public ResponseBuilder
    {
    public:
        DataResponseBuilder();
        ~DataResponseBuilder();

        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif //AHRS_DATARESPONSEBUILDER_H
