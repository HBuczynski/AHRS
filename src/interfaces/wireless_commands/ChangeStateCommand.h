#ifndef CHANGESTATECOMMAND_H
#define CHANGESTATECOMMAND_H

#include "Command.h"
#include <common/FeederStates.h>

namespace communication
{
    class ChangeStateCommand : public Command
    {
    public:
        ChangeStateCommand(FeederStateCode feederStateCode);
        ~ChangeStateCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        FeederStateCode getFeederStateCode() const;
        void setFeederStateCode(const FeederStateCode &feederStateCode);

    private:
        virtual void initializeDataSize() override;

        FeederStateCode feederStateCode_;
    };
}

#endif // CHANGESTATECOMMAND_H
