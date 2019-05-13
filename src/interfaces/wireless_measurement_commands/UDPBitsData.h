#ifndef UDPBITSDATA_H
#define UDPBITSDATA_H

#include "MeasuringData.h"

namespace communication
{
    class UDPBitsData final : public MeasuringData
    {
    public:
        UDPBitsData();
        ~UDPBitsData();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(MeasuringDataVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // UDPBITSDATA_H
