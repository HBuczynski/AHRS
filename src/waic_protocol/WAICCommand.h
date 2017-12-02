#ifndef WAIC_COMMAND_H
#define WAIC_COMMAND_H

#include "WAICFrame.h"

namespace communication
{
    enum WAICCommandType : uint8_t
    {
        INIT_CONNECTION,
        CALIBRATE_MAGNETOMETER,
        COLLECT_DATA,
        END_CONNECTION
    };

    class WAICCommand : public WAICFrame
    {
    public:
        WAICCommand(uint8_t dataSizeIn, WAICCommandType commandTypeIn);
        virtual ~WAICCommand();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;

        const WAICCommandType& getCommandType();


    protected:
        WAICCommandType commandType;

    };
}
#endif