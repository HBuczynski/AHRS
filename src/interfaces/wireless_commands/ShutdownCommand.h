#ifndef SHUTDOWNCOMMAND_H
#define SHUTDOWNCOMMAND_H

#include "Command.h"

namespace communication
{
    class ShutdownCommand : public Command
    {
    public:
        ShutdownCommand();
        ~ShutdownCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}


#endif // SHUTDOWNCOMMAND_H
