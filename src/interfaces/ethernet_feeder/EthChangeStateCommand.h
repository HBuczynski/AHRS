#ifndef ETHCHANGESTATECOMMAND_H
#define ETHCHANGESTATECOMMAND_H

#include "EthFeederCommand.h"
#include <common/FeederStates.h>

namespace communication
{
    class EthChangeStateCommand : public EthFeederCommand
    {
    public:
        EthChangeStateCommand(FeederStateCode feederState);
        ~EthChangeStateCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(EthFeederCommandVisitor& visitor) override;

        FeederStateCode getFeederState() const;
        void setFeederState(const FeederStateCode &feederState);

    private:
        virtual void initializeDataSize() override;

        FeederStateCode feederState_;
    };
}

#endif // ETHCHANGESTATECOMMAND_H
