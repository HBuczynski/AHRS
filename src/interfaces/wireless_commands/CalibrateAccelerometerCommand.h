#ifndef CALIBRATEACCELEROMETERCOMMAND_H
#define CALIBRATEACCELEROMETERCOMMAND_H

#include "Command.h"

#include <string>

namespace communication
{
    enum class AccelAction : uint8_t
    {
        APPROVE = 0x01,
        ENABLE = 0x02,
        DISABLE = 0x03,
        NEXT_AXIS = 0x04
    };

    class CalibrateAccelerometerCommand final : public Command
    {
    public:
        CalibrateAccelerometerCommand(uint8_t axis, AccelAction action);
        ~CalibrateAccelerometerCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        uint8_t getAxis() const noexcept;
        void setAxis(uint8_t axis) noexcept;

        void setAction(AccelAction action) noexcept;
        AccelAction getAction() const noexcept;

    private:
        virtual void initializeDataSize() override;

        uint8_t axis_;
        AccelAction action_;
    };
}

#endif // CALIBRATEACCELEROMETERCOMMAND_H
