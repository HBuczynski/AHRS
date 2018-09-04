#ifndef AHRS_AIRCRAFTPARAMETERS_H
#define AHRS_AIRCRAFTPARAMETERS_H

#include <string>

namespace config
{
    struct AircraftParameters
    {
        char name[32];
        double calibrationX;
        double calibrationY;
        double calibrationZ;
    };
}
#endif