#ifndef AHRS_CURRENTSTATEBUILDER_H
#define AHRS_CURRENTSTATEBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class CurrentStateBuilder final : public ResponseBuilder
    {
    public:
        CurrentStateBuilder();
        ~CurrentStateBuilder();

        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}


#endif