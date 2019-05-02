#ifndef AHRS_FEEDERCOMMAND_H
#define AHRS_FEEDERCOMMAND_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class FeederCommandVisitor;

    enum FeederCommandType : uint8_t
    {
        CALIBRATE_MAGNETOMETER_DEMAND = 0x05,
        COMMAND_WRAPPER = 0x10
    };

    class FeederCommand : public Frame
    {
    public:
        FeederCommand(uint8_t dataSizeIn, FeederCommandType commandTypeIn);
        virtual ~FeederCommand();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(FeederCommandVisitor& visitor) = 0;

        const FeederCommandType& getCommandType() const;

    protected:
        virtual void initializeDataSize() = 0;

        FeederCommandType commandType_;

    };
}

#endif
