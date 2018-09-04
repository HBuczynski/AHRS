#ifndef AHRS_GUIPLANEBUILDER_H
#define AHRS_GUIPLANEBUILDER_H

#include "GUIResponseBuilder.h"

namespace communication
{
    class GUIPlaneBuilder final : public GUIResponseBuilder
    {
    public:
        GUIPlaneBuilder();
        ~GUIPlaneBuilder();

        std::unique_ptr<GUIResponse> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif