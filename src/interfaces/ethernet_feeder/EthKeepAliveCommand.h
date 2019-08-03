#ifndef EthKeepAliveCommand_H
#define EthKeepAliveCommand_H

#include "EthFeederCommand.h"

namespace communication
{
    class EthKeepAliveCommand : public EthFeederCommand
    {
    public:
        EthKeepAliveCommand();
        ~EthKeepAliveCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(EthFeederCommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // EthKeepAliveCommand_H
