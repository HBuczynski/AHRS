#ifndef ETHCHANGESTATECOMMAND_H
#define ETHCHANGESTATECOMMAND_H

#include "EthFeederCommand.h"

namespace communication
{
    class EthChangeStateCommand : public EthFeederCommand
    {
    public:
        EthChangeStateCommand();
        ~EthChangeStateCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(EthFeederCommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // ETHCHANGESTATECOMMAND_H
