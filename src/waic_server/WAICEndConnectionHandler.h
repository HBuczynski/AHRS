#ifndef AHRS_BLACK_BOX_WAICENDCONNECTIONHANDLER_H
#define AHRS_BLACK_BOX_WAICENDCONNECTIONHANDLER_H

#include "WAICCommandHandler.h"

#include <functional>

namespace communication
{
    class WAICEndConnectionHandler final : public WAICCommandHandler
    {
    public:
        WAICEndConnectionHandler(std::function<void (uint8_t) >);
        ~WAICEndConnectionHandler();

        virtual std::shared_ptr<WAICResponse> handler(const std::vector<uint8_t>& vec, uint8_t clientID) override;

    private:
        std::function<void (uint8_t) > removeClientFromList;
    };
}

#endif
