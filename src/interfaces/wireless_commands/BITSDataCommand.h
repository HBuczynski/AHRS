#ifndef BITSDATACOMMAND_H
#define BITSDATACOMMAND_H

#include "Command.h"

namespace communication
{
    class BITSDataCommand final : public Command
    {
    public:
        BITSDataCommand();
        ~BITSDataCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // BITSDATACOMMAND_H
