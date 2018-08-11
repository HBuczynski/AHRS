#ifndef AHRS_UICOMMANDBUILDER_H
#define AHRS_UICOMMANDBUILDER_H

#include "UICommand.h"

#include <memory>
#include <vector>

namespace communication
{
    class UICommandBuilder
    {
    public:
        virtual std::unique_ptr<UICommand> create(const std::vector<uint8_t> &commandInBytes) = 0;

    protected:
        const uint8_t initialDataPosition = 7;
    };
}

#endif