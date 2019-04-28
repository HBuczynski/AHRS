#ifndef AHRS_CALLIBRATEMAGNETOMETERDATA_H
#define AHRS_CALLIBRATEMAGNETOMETERDATA_H

#include "Command.h"

#include <string>

namespace communication
{
    enum class Action : uint8_t
    {
        APPROVE = 0x01,
        REJECT = 0x02
    };

    class CallibrateMagnetometerCommand final : public Command
    {
    public:
        CallibrateMagnetometerCommand(Action status);
        ~CallibrateMagnetometerCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        void setPlaneStatus(Action status);
        const Action& getPlaneStatus() const;

    private:
        virtual void initializeDataSize() override;

        Action status_;
    };
}
#endif
