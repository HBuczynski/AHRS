#ifndef AHRS_RESPONSEBUILDER_H
#define AHRS_RESPONSEBUILDER_H

#include "Response.h"
#include <memory>

namespace communication
{
    class ResponseBuilder
    {
    public:
        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) = 0;

    };
}

#endif
