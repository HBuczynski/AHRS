#ifndef GUIWIRELESSCOMWRAPPERBUILDER_H
#define GUIWIRELESSCOMWRAPPERBUILDER_H

#include "GUIResponseBuilder.h"

namespace communication
{
    class GUIWirelessComWrapperBuilder final : public GUIResponseBuilder
    {
    public:
        GUIWirelessComWrapperBuilder();
        ~GUIWirelessComWrapperBuilder();

        virtual std::unique_ptr<GUIResponse> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // GUIWIRELESSCOMWRAPPERBUILDER_H
