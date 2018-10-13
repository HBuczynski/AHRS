#ifndef AHRS_UIMAINSTATES_H
#define AHRS_UIMAINSTATES_H


enum class UIMainStateCode : uint8_t
{
    IDLE = 0x01,
    WELCOME_PAGE = 0x02,
    ESTABLISHING_CONNECTION = 0x03
};

#endif //AHRS_UIMAINSTATES_H
