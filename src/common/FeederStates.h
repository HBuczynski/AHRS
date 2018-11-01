#ifndef AHRS_FEEDERBITS_H
#define AHRS_FEEDERBITS_H

enum class FeederBITs : uint8_t
{
    GPS_BITS = 0x01,
    IMU_1_BITS = 0x02,
    IMU_2_BITS = 0x03,
};

enum class FeederExternalStateCode : uint8_t
{
    IDLE = 0x01,
    ERROR = 0x03,
    MASTER_SENDING = 0x05,
    REDUNDANT_SENDING = 0x06,
    REGISTERED_USERS = 0x07,
    RESET = 0x08,
    SHUTDOWN = 0x09
};

#endif //AHRS_FEEDERBITS_H
