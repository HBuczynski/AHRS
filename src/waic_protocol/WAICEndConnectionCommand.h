#ifndef AHRS_BLACK_BOX_WAICENDCONNECTIONCOMMAND_H
#define AHRS_BLACK_BOX_WAICENDCONNECTIONCOMMAND_H

#include "WAICCommand.h"

namespace communication
{
    class WAICEndConnectionCommand final : public WAICCommand
    {
    public:
        WAICEndConnectionCommand();
        WAICEndConnectionCommand(const std::vector<uint8_t>& frameBytes);
        ~WAICEndConnectionCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
    };
}

#endif

