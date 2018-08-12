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
        NOTIFICATION = 40
    };

    enum class InterfaceType :uint8_t
    {
        SCHEDULER_FEEDER = 1,
        ETHERNET_FEEDER = 2,
        COMMUNICATION_PROCESS_FEEDER = 3,
        SCHEDULER_UI = 4,
        COMMUNICATION_PROCESS_UI = 5,
        WIRELESS = 6,
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

        static const uint8_t MEASUREMENT_DATA_TYPE_POSITION = 6;
        static const uint8_t RESPONSE_TYPE_POSITION = 6;
        static const uint8_t NOTIFICATION_TYPE_POSITION = 6;
        static const uint8_t COMMAND_TYPE_POSITION = 6;
        static const uint8_t INITIAL_DATA_POSITION = 7;

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
