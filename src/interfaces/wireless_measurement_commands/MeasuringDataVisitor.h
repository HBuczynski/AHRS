#ifndef AHRS_MEASURINGDATAVISITOR_H
#define AHRS_MEASURINGDATAVISITOR_H

#include "ImuData.h"
#include "GpsData.h"
#include "FlightData.h"

namespace communication
{
    class MeasuringDataVisitor
    {
    public:
        MeasuringDataVisitor() {};
        virtual ~MeasuringDataVisitor() {};

        virtual void visit(ImuData& data) = 0;
        virtual void visit(GpsData& data) = 0;
        virtual void visit(FlightData& data) = 0;
    };
}

#endif //AHRS_MEASURINGDATAVISITOR_H
