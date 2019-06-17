#ifndef ETHFEEDERRESPONSEFACTORY_H
#define ETHFEEDERRESPONSEFACTORY_H

#include "EthFeederResponseBuilder.h"

namespace communication
{
    class EthFeederResponseFactory
    {
    public:
        EthFeederResponseFactory();
        ~EthFeederResponseFactory();

        std::unique_ptr<EthFeederResponse> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<EthFeederResponseBuilder> builder_;
    };
}


#endif // ETHFEEDERRESPONSEFACTORY_H
