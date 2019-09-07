#ifndef GUIRESTARTRESPONSEBUILDER_H
#define GUIRESTARTRESPONSEBUILDER_H

#include "GUIResponseBuilder.h"

namespace communication
{
    class GUIRestartResponseBuilder final : public GUIResponseBuilder
    {
    public:
        GUIRestartResponseBuilder();
        ~GUIRestartResponseBuilder();

        virtual std::unique_ptr<GUIResponse> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // GUIRESTARTRESPONSEBUILDER_H
