#ifndef AHRS_MEASUREMENTS_H
#define AHRS_MEASUREMENTS_H

#include <cstdint>

struct FlightMeasurements
{
    uint64_t timestamp;

    double roll;
    double pitch;
    double altitude;
    double pressure;
    double machNo;
    double groundSpeed;
    double heading;
    double verticalSpeed;
    double latitude;
    char latitudeDirection;
    double longitude;
    char longitudeDirection;
    double turnCoordinator;
    double slipSkid;
};

struct GPSData
{
    uint64_t timestamp;

    double latitude;
    char latitudeDirection;

    double longitude;
    char longitudeDirection;

    double altitude;

    uint8_t fixQuality;
    uint8_t numberOfSatellites;

    char receiverWarning;

    double groundSpeed;
    double course;
};

struct IMUData
{
    uint64_t timestamp;

    double accelX;
    double accelY;
    double accelZ;

    double yaw;
    double pitch;
    double roll;
};

struct FeederProperties
{
    uint64_t timestamp;
    uint8_t mode;
    double bandwith;

    double temperature;
    double power;

    double core1;
    double core2;
    double core3;
    double core4;
};

struct FeederGeneralData
{
    FlightMeasurements flightMeasurements;
    GPSData gpsData;
    IMUData imuData;
};

#endif
