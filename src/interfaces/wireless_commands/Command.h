#ifndef WAIC_COMMAND_H
#define WAIC_COMMAND_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class CommandVisitor;

    enum CommandType : uint8_t
    {
        INIT_CONNECTION = 10,
        HANDSHAKE = 11,
        CALIBRATE_MAGNETOMETER = 20,
        CALIBRATE_ACCELEROMETER = 21,
        REMOVE_PLANE_DATA = 25,
        SET_PLANE_NAME = 30,
        COLLECT_DATA = 40,
        END_CONNECTION = 50,
        CALIBRATION_STATUS = 60,
        START_ACQ = 70,
        STOP_ACQ = 75,
        CURRENT_STATE = 80,
        CHANGE_FEEDER_STATE = 81,
        PERFORM_BIT = 90,
        CALIBRATE_DATA = 100,
        BITS_DATA = 110,
        SET_HASH = 120,
        UDP_BITS = 130,
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
