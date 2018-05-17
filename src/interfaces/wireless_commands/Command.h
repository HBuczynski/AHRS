#ifndef WAIC_COMMAND_H
#define WAIC_COMMAND_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class CommandVisitor;

    enum CommandType : uint8_t
    {
        INIT_CONNECTION = 10,
        CALIBRATE_MAGNETOMETER = 20,
        SET_PLANE_MAGNETOMETER_DATA = 30,
        COLLECT_DATA = 40,
        END_CONNECTION = 50
    };

    class Command : public Frame
    {
    public:
        Command(uint8_t dataSizeIn, CommandType commandTypeIn);
        virtual ~Command();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(CommandVisitor& visitor) = 0;

        const CommandType& getCommandType() const;

    protected:
        virtual void initializeDataSize() = 0;

        CommandType commandType_;

    };
}
#endif
