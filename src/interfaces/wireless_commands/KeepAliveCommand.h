#ifndef KEEPALIVECOMMAND_H
#define KEEPALIVECOMMAND_H

#include "Command.h"

namespace communication
{
    class KeepAliveCommand : public Command
    {
    public:
        KeepAliveCommand();
        ~KeepAliveCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // KEEPALIVECOMMAND_H
