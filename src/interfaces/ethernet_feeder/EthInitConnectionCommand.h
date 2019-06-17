#ifndef ETHINITCONNECTIONCOMMAND_H
#define ETHINITCONNECTIONCOMMAND_H

#include "EthFeederCommand.h"

namespace communication
{
    class EthInitConnectionCommand : public EthFeederCommand
    {
    public:
        EthInitConnectionCommand();
        ~EthInitConnectionCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(EthFeederCommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}


#endif // ETHINITCONNECTIONCOMMAND_H
