#ifndef ETHFEEDERRESPONSEBUILDER_H
#define ETHFEEDERRESPONSEBUILDER_H

#include "EthFeederResponse.h"
#include <memory>

namespace communication
{
    class EthFeederResponseBuilder
    {
    public:
        virtual std::unique_ptr<EthFeederResponse> create(const std::vector<uint8_t> &dataInBytes) = 0;
    };
}

#endif // ETHFEEDERRESPONSEBUILDER_H
