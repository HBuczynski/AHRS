#ifndef AHRS_STARTACQUISITIONCOMMAND_H
#define AHRS_STARTACQUISITIONCOMMAND_H

#include "Command.h"

namespace communication
{
    class StartAcquisitionCommand : public Command
    {
    public:
        StartAcquisitionCommand();
        ~StartAcquisitionCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}


#endif
