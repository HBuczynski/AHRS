#ifndef AHRS_BLACK_BOX_WAICINITCONNECTIONHANDLER_H
#define AHRS_BLACK_BOX_WAICINITCONNECTIONHANDLER_H

#include <waic_client/Client.h>

#include "CommandExecutor.h"

#include <functional>
#include <utility>

namespace communication
{
    class InitConnectionExecutor final : public CommandExecutor
    {
    public:
        InitConnectionExecutor(std::function<void (std::pair<std::shared_ptr<Client>, uint8_t>) >);
        ~InitConnectionExecutor();

        virtual std::shared_ptr<Response> execute(const std::vector<uint8_t>& vec, uint8_t clientID) override;

    private:
        std::function<void (std::pair<std::shared_ptr<Client>, uint8_t>) > insertNewClient;
    };
}
#endif
