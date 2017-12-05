#ifndef AHRS_BLACK_BOX_WAICCOMMANDHANDLER_H
#define AHRS_BLACK_BOX_WAICCOMMANDHANDLER_H

#include <vector>
#include <cstdint>
#include <memory>

#include <waic_protocol/WAICResponse.h>

namespace communication
{
    class WAICCommandHandler
    {
    public:
        WAICCommandHandler();
        virtual ~WAICCommandHandler();

        virtual std::shared_ptr<WAICResponse> handler(const std::vector<uint8_t>& vec, uint8_t clientID) = 0;

    };
}

#endif
