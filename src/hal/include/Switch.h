#ifndef AHRS_SWITCH_H
#define AHRS_SWITCH_H

#include "GPIOInterface.h"

#include "../../../3rd_party/PIGPIO/pigpio.h"


namespace hardware
{
    class Switch final : public GPIOInterface
    {
    public:
        Switch(GPIO gpio);
        ~Switch();

        bool registerHandler(gpioISRFuncEx_t fun, const int &edge, const int &timeout = 0, void *intData = nullptr);


#ifdef VIRTUAL_BOARD
        const int a = 65;
#endif
    };
}

#endif