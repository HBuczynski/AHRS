#ifndef AHRS_SETPLANEMAGNETOMETERDATACOMMAND_H
#define AHRS_SETPLANEMAGNETOMETERDATACOMMAND_H

#include "Command.h"
#include <string>

namespace communication
{
    class SetPlaneMagnetometerCommand : public Command
    {
    public:
        SetPlaneMagnetometerCommand();
        ~SetPlaneMagnetometerCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        void setPlaneName(const std::string &name);
        const std::string &getPlaneName() const;

    private:
        std::string planeName_;

    };
}
#endif
