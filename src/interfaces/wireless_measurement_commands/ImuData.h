#ifndef AHRS_BLACK_BOX_WAICIMUDATA_H
#define AHRS_BLACK_BOX_WAICIMUDATA_H

#include "MeasuringData.h"

namespace communication
{
    class ImuData final : public MeasuringData
    {
    public:
        ImuData(uint8_t measurement);
        ~ImuData();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(MeasuringDataVisitor& visitor) override;

        uint8_t getMeasurement() const;

    private:
        virtual void initializeDataSize() override;

        uint8_t measurement_;
    };
}

#endif