#ifndef RESTARTCOMMAND_H
#define RESTARTCOMMAND_H

#include "Command.h"

namespace communication
{
    class RestartCommand : public Command
    {
    public:
        RestartCommand();
        ~RestartCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // RESTARTCOMMAND_H
