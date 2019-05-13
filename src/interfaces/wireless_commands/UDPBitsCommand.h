#ifndef UDPBITSCOMMAND_H
#define UDPBITSCOMMAND_H

#include "Command.h"

namespace communication
{
    class UDPBitsCommand final : public Command
    {
    public:
        UDPBitsCommand();
        ~UDPBitsCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // UDPBITSCOMMAND_H
