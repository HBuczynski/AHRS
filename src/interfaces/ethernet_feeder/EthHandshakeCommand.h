#ifndef ETHHANDSHAKECOMMAND_H
#define ETHHANDSHAKECOMMAND_H

#include "EthFeederCommand.h"
#include <config_reader/FeederParameters.h>

namespace communication
{
    class EthHandshakeCommand : public EthFeederCommand
    {
    public:
        EthHandshakeCommand(config::FeederMode mode);
        ~EthHandshakeCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(EthFeederCommandVisitor& visitor) override;

        config::FeederMode getMode() const;
        void setMode(const config::FeederMode &mode);

    private:
        virtual void initializeDataSize() override;

        config::FeederMode mode_;
    };
}

#endif // ETHHANDSHAKECOMMAND_H
