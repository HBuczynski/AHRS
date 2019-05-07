#ifndef AHRS_FLIGHTDATA_H
#define AHRS_FLIGHTDATA_H

#include "MeasuringData.h"
#include <../../common/Measurements.h>

namespace communication
{
    class FeederData final : public MeasuringData
    {
    public:
        FeederData(FeederGeneralData measurements);
        ~FeederData();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(MeasuringDataVisitor& visitor) override;

        FeederGeneralData getMeasurements() const;
        void setMeasurements(FeederGeneralData measurements);

    private:
        virtual void initializeDataSize() override;

        FeederGeneralData measurements_;
    };
}

#endif
