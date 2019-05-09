#ifndef SETHASHCOMMAND_H
#define SETHASHCOMMAND_H

#include "Command.h"

namespace communication
{
    class SetHashCommand : public Command
    {
    public:
        SetHashCommand(uint32_t hash);
        ~SetHashCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        void setHash(uint32_t hash);
        uint32_t getHash() const noexcept;

    private:
        virtual void initializeDataSize() override;

        uint32_t hash_;

    };
}

#endif // SETHASHCOMMAND_H
