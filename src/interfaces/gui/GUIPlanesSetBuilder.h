#ifndef AHRS_GUI_PLANES_SETBUILDER_H
#define AHRS_GUI_PLANES_SETBUILDER_H

#include "GUICommandBuilder.h"

namespace communication
{
    class GUIPlanesSetBuilder final : public GUICommandBuilder
    {
    public:
        GUIPlanesSetBuilder();
        ~GUIPlanesSetBuilder();

        virtual std::unique_ptr<GUICommand> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif
