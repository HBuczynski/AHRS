#ifndef AHRS_MEASUREMENTS_H
#define AHRS_MEASUREMENTS_H

struct FlightMeasurements
{
    float roll;
    float pitch;
    float altitude;
    float pressure;
    float machNo;
    float groundSpeed;
    float heading;
    float verticalSpeed;
    float latitude;
    float longitude;
    float turnCoordinator;
    float slipSkid;
};

#endif