#ifndef AHRS_GUI_CALIBRATIONBUILDER_H
#define AHRS_GUI_CALIBRATIONBUILDER_H

#include "GUICommandBuilder.h"

namespace communication
{
    class GUICallibrationBuilder final : public GUICommandBuilder
    {
    public:
        GUICallibrationBuilder();
        ~GUICallibrationBuilder();

        virtual std::unique_ptr<GUICommand> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif
