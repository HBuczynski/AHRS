#ifndef HANDSHAKECOMMAND_H
#define HANDSHAKECOMMAND_H

#include "Command.h"
#include <config_reader/FeederParameters.h>

namespace communication
{
    class HandshakeCommand : public Command
    {
    public:
        HandshakeCommand(config::FeederMode mode);
        ~HandshakeCommand();

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


#endif // HANDSHAKECOMMAND_H
