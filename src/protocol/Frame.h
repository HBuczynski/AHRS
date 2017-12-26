#ifndef AHRS_BLACK_BOX_WAICFRAME_H
#define AHRS_BLACK_BOX_WAICFRAME_H

#include <string>
#include <vector>

namespace communication
{
    const uint8_t END_STRING_IN_FRAME = '#';

    enum FrameType : uint8_t
    {
        COMMAND = 10,
        RESPONSE = 20,
        MEASUREMENT_DATA = 30
    };

    class Frame
    {
    public:
        Frame(FrameType frameTypeIn, uint16_t dataSizeIn);
        virtual ~Frame();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;

        std::vector<uint8_t > getHeader() const;

        const uint8_t& getPacketNumber() const;
        void setPacketNumber(uint8_t number);

        const uint16_t& getDataSize() const;
        void setDataSize(uint16_t dataSize);

        const uint8_t& getSystemVersion() const;
        const FrameType& getFrameType() const;

    protected:
        virtual void initializeDataSize() = 0;

        uint8_t systemVersion_;
        FrameType frameType_;
        uint8_t packetNumber_;
        uint16_t dataSize_;
    };
}

#endif
