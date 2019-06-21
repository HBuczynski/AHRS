#ifndef HANDSHAKECOMMAND_H
#define HANDSHAKECOMMAND_H

#include "Command.h"

namespace communication
{
    class HandshakeCommand : public Command
    {
    public:
        HandshakeCommand();
        ~HandshakeCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}


#endif // HANDSHAKECOMMAND_H
