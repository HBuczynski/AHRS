#ifndef AHRS_GUIINFORMATIONWINDOWBUILDER_H
#define AHRS_GUIINFORMATIONWINDOWBUILDER_H

#include "GUICommandBuilder.h"

namespace communication
{
    class GUIInformationWindowBuilder final : public GUICommandBuilder
    {
    public:
        GUIInformationWindowBuilder();
        ~GUIInformationWindowBuilder();

        std::unique_ptr<GUICommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif