#ifndef AHRS_BLACK_BOX_WAICINITCONNECTIONHANDLER_H
#define AHRS_BLACK_BOX_WAICINITCONNECTIONHANDLER_H

#include <waic_client/WAICClient.h>

#include "WAICCommandHandler.h"

#include <functional>
#include <utility>

namespace communication
{
    class WAICInitConnectionHandler final : public WAICCommandHandler
    {
    public:
        WAICInitConnectionHandler(std::function<void (std::pair<std::shared_ptr<WAICClient>, uint8_t>) >);
        ~WAICInitConnectionHandler();

        virtual std::shared_ptr<WAICResponse> handler(const std::vector<uint8_t>& vec, uint8_t clientID) override;

    private:
        std::function<void (std::pair<std::shared_ptr<WAICClient>, uint8_t>) > insertNewClient;
    };
}
#endif
