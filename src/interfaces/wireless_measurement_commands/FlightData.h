#ifndef AHRS_FLIGHTDATA_H
#define AHRS_FLIGHTDATA_H

#include "MeasuringData.h"
#include <../../common/Measurements.h>

namespace communication
{
    class FlightData final : public MeasuringData
    {
    public:
        FlightData(FlightMeasurements measurements);
        ~FlightData();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(MeasuringDataVisitor& visitor) override;

        FlightMeasurements getMeasurements() const;
        void setMeasurements(FlightMeasurements measurements);

    private:
        virtual void initializeDataSize() override;

        FlightMeasurements measurements_;
    };
}

#endif