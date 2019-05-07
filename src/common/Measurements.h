#ifndef AHRS_MEASUREMENTS_H
#define AHRS_MEASUREMENTS_H

#include <cstdint>

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
    char latitudeDirection;
    float longitude;
    char longitudeDirection;
    float turnCoordinator;
    float slipSkid;
};

struct GPSData
{
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;

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

    double processorConsumption;
};

struct FeederGeneralData
{
    FeederProperties feederProperties;
    FlightMeasurements flightMeasurements;
    GPSData gpsData;
    IMUData imuData;
};

#endif
