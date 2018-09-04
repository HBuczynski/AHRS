#ifndef AHRS_GUICOMMANDBUILDER_H
#define AHRS_GUICOMMANDBUILDER_H

#include "GUICommand.h"

#include <memory>
#include <vector>

namespace communication
{
    class GUICommandBuilder
    {
    public:
        virtual std::unique_ptr<GUICommand> create(const std::vector<uint8_t> &commandInBytes) = 0;
    };
}

#endif 