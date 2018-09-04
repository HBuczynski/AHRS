#ifndef AHRS_GUICOMMANDFACTORY_H
#define AHRS_GUICOMMANDFACTORY_H


#include "GUICommand.h"
#include "GUICommandBuilder.h"

#include <memory>

namespace communication
{
    class GUICommandFactory
    {
    public:
        GUICommandFactory();
        ~GUICommandFactory();

        std::unique_ptr<GUICommand> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<GUICommandBuilder> builder_;
    };
}


#endif 