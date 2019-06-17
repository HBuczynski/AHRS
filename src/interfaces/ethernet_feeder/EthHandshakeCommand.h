#ifndef ETHHANDSHAKECOMMAND_H
#define ETHHANDSHAKECOMMAND_H

#include "EthFeederCommand.h"

namespace communication
{
    class EthHandshakeCommand : public EthFeederCommand
    {
    public:
        EthHandshakeCommand();
        ~EthHandshakeCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(EthFeederCommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // ETHHANDSHAKECOMMAND_H
