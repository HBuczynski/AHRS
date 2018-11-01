#ifndef AHRS_GUIWINDOWRESPONSEBUILDER_H
#define AHRS_GUIWINDOWRESPONSEBUILDER_H

#include "GUIResponseBuilder.h"

namespace communication
{
    class GUIWindowResponseBuilder final : public GUIResponseBuilder
    {
    public:
        GUIWindowResponseBuilder();
        ~GUIWindowResponseBuilder();

        std::unique_ptr<GUIResponse> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif