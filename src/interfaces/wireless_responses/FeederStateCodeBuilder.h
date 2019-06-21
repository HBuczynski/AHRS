#ifndef AHRS_FeederStateCodeBuilder_H
#define AHRS_FeederStateCodeBuilder_H

#include "ResponseBuilder.h"

namespace communication
{
    class FeederStateCodeBuilder final : public ResponseBuilder
    {
    public:
        FeederStateCodeBuilder();
        ~FeederStateCodeBuilder();

        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}


#endif
