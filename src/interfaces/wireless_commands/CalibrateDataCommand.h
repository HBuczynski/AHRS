#ifndef CALIBRATEDATACOMMAND_H
#define CALIBRATEDATACOMMAND_H

#include "Command.h"

namespace communication
{
    class CalibrateDataCommand final : public Command
    {
    public:
        CalibrateDataCommand();
        ~CalibrateDataCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // CALIBRATEDATACOMMAND_H
