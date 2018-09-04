#ifndef AHRS_GUIRESPONSEFACTORY_H
#define AHRS_GUIRESPONSEFACTORY_H

#include "GUIResponseBuilder.h"

namespace communication
{
    class GUIResponseFactory
    {
    public:
        GUIResponseFactory();
        ~GUIResponseFactory();

        std::unique_ptr<GUIResponse> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<GUIResponseBuilder> builder_;
    };
}

#endif