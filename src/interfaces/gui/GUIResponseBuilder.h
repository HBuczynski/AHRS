#ifndef AHRS_GUIRESPONSEBUILDER_H
#define AHRS_GUIRESPONSEBUILDER_H

#include "GUIResponse.h"
#include <memory>

namespace communication
{
    class GUIResponseBuilder
    {
    public:
        virtual std::unique_ptr<GUIResponse> create(const std::vector<uint8_t> &dataInBytes) = 0;
    };
}


#endif