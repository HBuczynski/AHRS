#ifndef STOPACQCOMMAND_H
#define STOPACQCOMMAND_H

#include "Command.h"

namespace communication
{
    class StopAcqCommand : public Command
    {
    public:
        StopAcqCommand();
        ~StopAcqCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // STOPACQCOMMAND_H
