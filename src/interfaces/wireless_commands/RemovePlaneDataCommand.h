#ifndef AHRS_REMOVEPLANEDATACOMMAND_H
#define AHRS_REMOVEPLANEDATACOMMAND_H

#include "Command.h"

#include <string>

namespace communication
{
    class RemovePlaneDataCommand final : public Command
    {
    public:
        RemovePlaneDataCommand(const std::string &name);
        ~RemovePlaneDataCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        void setPlaneName(const std::string &name);
        const std::string &getPlaneName() const;

    private:
        virtual void initializeDataSize() override;

        std::string planeName_;
    };
}

#endif //AHRS_REMOVEPLANEDATACOMMAND_H
