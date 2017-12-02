#ifndef AHRS_BLACK_BOX_WAIC_INIT_CONNECTION_COMMAND_H
#define AHRS_BLACK_BOX_WAIC_INIT_CONNECTION_COMMAND_H

#include "WAICCommand.h"

namespace communication
{
    class WAICInitConnectionCommand final : public WAICCommand
    {
    public:
        WAICInitConnectionCommand();
        WAICInitConnectionCommand(const std::vector<uint8_t>& frameBytes);
        ~WAICInitConnectionCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;

    private:
        uint16_t serverListenUDPPort;

    };
}

#endif