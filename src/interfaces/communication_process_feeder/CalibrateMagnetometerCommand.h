#ifndef AHRS_CALIBRATEMAGNETOMETERCOMMAND_H
#define AHRS_CALIBRATEMAGNETOMETERCOMMAND_H

#include "FeederCommand.h"

#include <string>

namespace communication
{
    class CalibrateMagnetometerCommand final : public FeederCommand
    {
    public:
        CalibrateMagnetometerCommand(const std::string& name);
        ~CalibrateMagnetometerCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FeederCommandVisitor& visitor) override;

        void setPlaneName(const std::string &name);
        const std::string &getPlaneName() const;

    private:
        virtual void initializeDataSize() override;

        std::string planeName_;
    };
}
#endif