#ifndef AHRS_BLACK_BOX_WAICENDCONNECTIONHANDLER_H
#define AHRS_BLACK_BOX_WAICENDCONNECTIONHANDLER_H

#include "CommandExecutor.h"

#include <functional>
#include <waic_server/ClientThreadTCP.h>

namespace communication
{
    class EndConnectionExecutor final : public CommandExecutor
    {
    public:
        EndConnectionExecutor(std::function<void (uint8_t) > callbackFunction, ClientThreadTCP *client);
        ~EndConnectionExecutor();

        virtual std::shared_ptr<Response> execute(const std::vector<uint8_t>& vec, uint8_t clientID) override;

    private:
        std::function<void (uint8_t) > removeClientFromList;
        ClientThreadTCP *client_;
    };
}

#endif
