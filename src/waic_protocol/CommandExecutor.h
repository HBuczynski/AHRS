#ifndef AHRS_BLACK_BOX_WAICCOMMANDHANDLER_H
#define AHRS_BLACK_BOX_WAICCOMMANDHANDLER_H

#include <vector>
#include <cstdint>
#include <memory>

#include "Response.h"

namespace communication
{
    class CommandExecutor
    {
    public:
        CommandExecutor();
        virtual ~CommandExecutor();

        virtual std::shared_ptr<Response> execute(const std::vector<uint8_t>& vec, uint8_t clientID) = 0;

    };
}

#endif
