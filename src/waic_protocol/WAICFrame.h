#ifndef AHRS_BLACK_BOX_WAICFRAME_H
#define AHRS_BLACK_BOX_WAICFRAME_H

#include <string>
#include <vector>

#include <utility/BytesConverter.h>

namespace communication
{
    enum WAICFrameType : uint8_t
    {
        COMMAND,
        RESPONSE,
        MEASUREMENT_DATA
    };

    class WAICFrame
    {
    public:
        WAICFrame(WAICFrameType frameTypeIn, uint8_t dataSizeIn);
        virtual ~WAICFrame();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;

        std::vector<uint8_t > getHeader();

        const uint8_t& getPacketNumber();
        void setPacketNumber(uint8_t number);

        const uint8_t& getSystemVersion();
        const uint8_t& getDataSize();
        const WAICFrameType& getFrameType();

    protected:
        uint8_t systemVersion;
        WAICFrameType frameType;
        uint8_t packetNumber;
        uint8_t dataSize;
    };
}

#endif
