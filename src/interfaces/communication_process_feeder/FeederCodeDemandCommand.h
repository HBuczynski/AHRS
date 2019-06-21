#ifndef FEEDERCODEDEMANDCOMMAND_H
#define FEEDERCODEDEMANDCOMMAND_H

#include "FeederCommand.h"
#include <common/FeederStates.h>

namespace communication
{
    class FeederCodeDemandCommand final : public FeederCommand
    {
    public:
        FeederCodeDemandCommand(FeederStateCode code);
        ~FeederCodeDemandCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FeederCommandVisitor& visitor) override;

        FeederStateCode getStateCode() const;
        void setAckType(FeederStateCode code);

    private:
        virtual void initializeDataSize() override;

        FeederStateCode code_;
    };
}

#endif // FEEDERCODEDEMANDCOMMAND_H
