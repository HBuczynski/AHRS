#ifndef AHRS_GUIINFORMATIONWINDOWBUILDER_H
#define AHRS_GUIINFORMATIONWINDOWBUILDER_H

#include "GUICommandBuilder.h"

namespace communication
{
    class GUIBITSBuilder final : public GUICommandBuilder
    {
    public:
        GUIBITSBuilder();
        ~GUIBITSBuilder();

        std::unique_ptr<GUICommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif
