#ifndef CHANGEFEEDERMODECOMMAND_H
#define CHANGEFEEDERMODECOMMAND_H

#include "Command.h"
#include <config_reader/FeederParameters.h>

namespace communication
{
    class ChangeFeederModeCommand : public Command
    {
    public:
        ChangeFeederModeCommand(config::FeederMode mode);
        ~ChangeFeederModeCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        config::FeederMode getMode() const;
        void setMode(const config::FeederMode &mode);

    private:
        virtual void initializeDataSize() override;

        config::FeederMode mode_;
    };
}


#endif // CHANGEFEEDERMODECOMMAND_H
