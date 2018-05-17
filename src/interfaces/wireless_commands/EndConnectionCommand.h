#ifndef AHRS_BLACK_BOX_WAICENDCONNECTIONCOMMAND_H
#define AHRS_BLACK_BOX_WAICENDCONNECTIONCOMMAND_H

#include "Command.h"

namespace communication
{
    class EndConnectionCommand final : public Command
    {
    public:
        EndConnectionCommand();
        ~EndConnectionCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif

