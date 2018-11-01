#ifndef AHRS_UIMAINSTATES_H
#define AHRS_UIMAINSTATES_H


enum class UIMainStateCode : uint8_t
{
    IDLE = 0x01,
    WELCOME_PAGE = 0x02,
    ESTABLISHING_CONNECTION = 0x03,
    COMMUNICATION_OK = 0x04,
    BITS_OK = 0x05,
    BITS_FALSE = 0x06
};

enum class UIExternalStateCode : uint8_t
{
    IDLE = 0x01,
    REDUNDANT = 0x03,
    MASTER = 0x04,
    ERROR = 0x05,
};

enum class PagesType : uint8_t
{
    WELCOME_PAGE,
    SYSTEM_SETUP_PAGE,
    CALLIBRATION_SETTING_PAGE,
    RESTART_PAGE,
    EXIT_PAGE,
    AHRS_PAGE,
    LOGS_PAGE,
    MENU_PAGE,
    CONNECTING_PAGE,
    INFORMATION_PAGE
};

#endif //AHRS_UIMAINSTATES_H
