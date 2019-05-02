#ifndef FEEDERWIRELESSWRAPPERCOMMAND_H
#define FEEDERWIRELESSWRAPPERCOMMAND_H

#include "FeederCommand.h"

namespace communication
{
    class FeederWirelessWrapperCommand final : public FeederCommand
    {
    public:
        FeederWirelessWrapperCommand(const std::vector<uint8_t> &data);
        ~FeederWirelessWrapperCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FeederCommandVisitor& visitor) override;

        const std::vector<uint8_t>& getDataFrame() const;
        void setDataFrame(const std::vector<uint8_t>& data);
    private:
        virtual void initializeDataSize() override;

        std::vector<uint8_t> data_;
    };
}

#endif // FEEDERWIRELESSWRAPPERCOMMAND_H
