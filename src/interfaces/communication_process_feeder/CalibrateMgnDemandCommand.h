#ifndef AHRS_CALIBRATEMAGNETOMETERCOMMAND_H
#define AHRS_CALIBRATEMAGNETOMETERCOMMAND_H

#include "FeederCommand.h"

#include <string>

namespace communication
{
    class CalibrateMgnDemandCommand final : public FeederCommand
    {
    public:
        CalibrateMgnDemandCommand(const std::string& name);
        ~CalibrateMgnDemandCommand();

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
