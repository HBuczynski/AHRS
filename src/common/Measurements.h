#ifndef AHRS_MEASUREMENTS_H
#define AHRS_MEASUREMENTS_H

struct FlightMeasurements
{
    float altitude;
    float groundSpeed;
    float heading;
    float verticalSpeed;
    float latitude;
    float longitude;
    float turnCoordinator;
};

#endif