#ifndef FMCHANGECHANNELCOMMAND_H
#define FMCHANGECHANNELCOMMAND_H

#include "FMCommand.h"

namespace communication
{
    class FMChangeChannelCommand final : public FMCommand
    {
    public:
        FMChangeChannelCommand(uint8_t processNumber);
        ~FMChangeChannelCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FMCommandVisitor& visitor) override;

        uint8_t getProcessNumber() const;
        void setProcessNumber(const uint8_t &processNumber);

    private:
        virtual void initializeDataSize() override;

        uint8_t processNumber_;
    };
}

#endif // FMCHANGECHANNELCOMMAND_H
