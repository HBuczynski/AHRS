#ifndef WAIC_COMMAND_H
#define WAIC_COMMAND_H

#include "Frame.h"

//#include "CommandVisitor.h"

namespace communication
{
    class CommandVisitor;

    enum CommandType : uint8_t
    {
        INIT_CONNECTION,
        CALIBRATE_MAGNETOMETER,
        COLLECT_DATA,
        END_CONNECTION
    };

    class Command : public Frame
    {
    public:
        Command(uint8_t dataSizeIn, CommandType commandTypeIn);
        virtual ~Command();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(CommandVisitor& visitor) = 0;

        const CommandType& getCommandType();

    protected:
        CommandType commandType;

    };
}
#endif