#ifndef AHRS_GUIWINDOWBUILDER_H
#define AHRS_GUIWINDOWBUILDER_H

#include "GUICommandBuilder.h"

namespace communication
{
    class GUIWindowBuilder final : public GUICommandBuilder
    {
    public:
        GUIWindowBuilder();
        ~GUIWindowBuilder();

        std::unique_ptr<GUICommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif