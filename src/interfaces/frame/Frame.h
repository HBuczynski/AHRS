#ifndef AHRS_BLACK_BOX_WAICFRAME_H
#define AHRS_BLACK_BOX_WAICFRAME_H

#include <string>
#include <vector>

namespace communication
{
    const uint8_t FRAME_INDEX = 1;
    const uint8_t INTERFACE_INDEX = 2;
    const uint8_t END_STRING_IN_FRAME = '#';

    enum class FrameType : uint8_t
    {
        RESPONSE = 10,
        MEASUREMENT_DATA = 20,
        COMMAND = 30,
    };

    enum class InterfaceType :uint8_t
    {
        MAIN_FEEDER = 1,
        EXTERNAL_FEEDER = 2,
        INTERNAL_FEEDER = 3,
        MAIN_UI = 4,
        MAIN_COMMUNICATION_UI = 5,
        REDUNDANT_COMMUNICATION_UI = 6,
        GUI = 7,
        WIRELESS = 8,
        ETHERNET = 9
    };

    class Frame
    {
    public:
        Frame(FrameType frameTypeIn, InterfaceType interfaceTypeIn, uint16_t dataSizeIn);
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
        const InterfaceType& getInterfaceType() const;

    protected:
        virtual void initializeDataSize() = 0;

        uint8_t systemVersion_;
        FrameType frameType_;
        InterfaceType interfaceType_;
        uint8_t packetNumber_;
        uint16_t dataSize_;
    };
}

#endif
