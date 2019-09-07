#ifndef GUISHUTDOWNRESPONSEBUILDER_H
#define GUISHUTDOWNRESPONSEBUILDER_H

#include "GUIResponseBuilder.h"

namespace communication
{
    class GUIShutdownResponseBuilder final : public GUIResponseBuilder
    {
    public:
        GUIShutdownResponseBuilder();
        ~GUIShutdownResponseBuilder();

        virtual std::unique_ptr<GUIResponse> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}


#endif // GUISHUTDOWNRESPONSEBUILDER_H
