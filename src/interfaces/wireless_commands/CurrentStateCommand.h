#ifndef AHRS_CURRENTSTATECOMMAND_H
#define AHRS_CURRENTSTATECOMMAND_H

#include "Command.h"

namespace communication
{
    class CurrentStateCommand : public Command
    {
    public:
        CurrentStateCommand();
        ~CurrentStateCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}


#endif