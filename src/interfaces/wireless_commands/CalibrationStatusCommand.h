#ifndef AHRS_CALIBRATIONSTATUSCOMMAND_H
#define AHRS_CALIBRATIONSTATUSCOMMAND_H

#include "Command.h"

namespace communication
{
    class CalibrationStatusCommand : public Command
    {
    public:
        CalibrationStatusCommand();
        ~CalibrationStatusCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif
