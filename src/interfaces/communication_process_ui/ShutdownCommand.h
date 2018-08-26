#ifndef AHRS_SHUTDOWNCOMMAND_H
#define AHRS_SHUTDOWNCOMMAND_H

#include "UICommand.h"

namespace communication
{
    class ShutdownCommand : public UICommand
    {
    public:
        ShutdownCommand();
        ~ShutdownCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UICommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif