#ifndef AHRS_FEEDERBITS_H
#define AHRS_FEEDERBITS_H

enum class FeederBITs : uint8_t
{
    GPS_BITS = 0x01,
    IMU_1_BITS = 0x02,
    IMU_2_BITS = 0x03,
};

#endif //AHRS_FEEDERBITS_H
