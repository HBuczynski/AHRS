#ifndef AHRS_MEASURINGDATAVISITOR_H
#define AHRS_MEASURINGDATAVISITOR_H

#include "ImuData.h"
#include "GpsData.h"
#include "FeederData.h"
#include "UDPBitsData.h"

namespace communication
{
    class MeasuringDataVisitor
    {
    public:
        MeasuringDataVisitor() {};
        virtual ~MeasuringDataVisitor() {};

        virtual void visit(ImuData& data) = 0;
        virtual void visit(GpsData& data) = 0;
        virtual void visit(FeederData& data) = 0;
        virtual void visit(UDPBitsData& data) = 0;
    };
}

#endif //AHRS_MEASURINGDATAVISITOR_H
