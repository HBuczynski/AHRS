#ifndef AHRS_CALLIBRATEMAGNETOMETERDATA_H
#define AHRS_CALLIBRATEMAGNETOMETERDATA_H

#include "Command.h"

#include <string>

namespace communication
{
    enum class PlaneStatus : uint8_t
    {
        NEW = 0x01,
        OLD = 0x02
    };

    class CallibrateMagnetometerCommand final : public Command
    {
    public:
        CallibrateMagnetometerCommand(const std::string &name, PlaneStatus status);
        ~CallibrateMagnetometerCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        void setPlaneName(const std::string &name);
        const std::string &getPlaneName() const;

        void setPlaneStatus(PlaneStatus status);
        const PlaneStatus& getPlaneStatus() const;

    private:
        virtual void initializeDataSize() override;

        std::string planeName_;
        PlaneStatus status_;
    };
}
#endif
