#ifndef HMINVALIDCONNECTIONCOMMAND_H
#define HMINVALIDCONNECTIONCOMMAND_H

#include "HMCommand.h"

namespace communication
{
    class HMInvalidConnectionCommand final : public HMCommand
    {
    public:
        HMInvalidConnectionCommand(uint8_t processNumber);
        ~HMInvalidConnectionCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(HMCommandVisitor& visitor) override;

        uint8_t getProcessNumber() const;
        void setProcessNumber(const uint8_t &processNumber);

    private:
        virtual void initializeDataSize() override;

        uint8_t processNumber_;
    };
}

#endif // HMINVALIDCONNECTIONCOMMAND_H
