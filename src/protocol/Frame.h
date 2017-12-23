#ifndef AHRS_BLACK_BOX_WAICFRAME_H
#define AHRS_BLACK_BOX_WAICFRAME_H

#include <string>
#include <vector>

#include <utility/BytesConverter.h>

namespace communication
{
    enum FrameType : uint8_t
    {
        COMMAND = 10,
        RESPONSE = 20,
        MEASUREMENT_DATA = 30
    };

    class Frame
    {
    public:
        Frame(FrameType frameTypeIn, uint8_t dataSizeIn);
        virtual ~Frame();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;

        std::vector<uint8_t > getHeader() const;

        const uint8_t& getPacketNumber() const;
        void setPacketNumber(uint8_t number);

        const uint8_t& getSystemVersion() const;
        const uint8_t& getDataSize() const;
        const FrameType& getFrameType() const;

    protected:
        uint8_t systemVersion;
        FrameType frameType;
        uint8_t packetNumber;
        uint8_t dataSize;
    };
}

#endif
