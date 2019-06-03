#ifndef GUISTOPACQBUILDER_H
#define GUISTOPACQBUILDER_H

#include "GUIResponseBuilder.h"

namespace communication
{
    class GUIStopAcqBuilder final : public GUIResponseBuilder
    {
    public:
        GUIStopAcqBuilder();
        ~GUIStopAcqBuilder();

        virtual std::unique_ptr<GUIResponse> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}


#endif // GUISTOPACQBUILDER_H
