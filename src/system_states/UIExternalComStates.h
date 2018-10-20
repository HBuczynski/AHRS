#ifndef AHRS_UIEXTERNALCOMSTATES_H
#define AHRS_UIEXTERNALCOMSTATES_H

enum class UIExternalStateCode : uint8_t
{
    IDLE = 0x01,
    REDUNDANT = 0x03,
    MASTER = 0x04,
    ERROR = 0x05,
};

#endif