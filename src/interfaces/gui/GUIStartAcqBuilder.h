#ifndef GUISTARTACQBUILDER_H
#define GUISTARTACQBUILDER_H

#include "GUIResponseBuilder.h"

namespace communication
{
    class GUIStartAcqBuilder final : public GUIResponseBuilder
    {
    public:
        GUIStartAcqBuilder();
        ~GUIStartAcqBuilder();

        virtual std::unique_ptr<GUIResponse> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // GUISTARTACQBUILDER_H
