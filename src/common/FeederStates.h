#ifndef AHRS_FEEDERBITS_H
#define AHRS_FEEDERBITS_H

enum class FeederBITs : uint8_t
{
    GPS_BITS = 0x01,
    IMU_1_BITS = 0x02,
    IMU_2_BITS = 0x03,
};

enum FeederStateCode : uint8_t
{
    CALLIBATION = 0x01,
    IDLE = 0x02,
    CONNECTION = 0x03,
    MAIN_ACQ = 0x04,
    ERROR = 0x05,
    FAULT_MANAGEMENT = 0x06,
    PERFORM_BIT = 0x07,
    REDUNDANT_ACQ = 0x08,
    REGISTERED_USERS = 0x09,
    SETTINNG = 0x10,
    STOP_ACQ = 0x11
};

#endif //AHRS_FEEDERBITS_H
