#ifndef AHRS_SETPLANECOMMAND_H
#define AHRS_SETPLANECOMMAND_H

#include "Command.h"
#include <string>

namespace communication
{
    class SetPlaneCommand : public Command
    {
    public:
        SetPlaneCommand(const std::string &name);
        ~SetPlaneCommand();

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
#endif
