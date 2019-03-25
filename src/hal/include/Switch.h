#ifndef AHRS_SWITCH_H
#define AHRS_SWITCH_H

#ifdef VIRTUAL_BOARD
#include <thread>
#include <atomic>
#include <map>
#endif

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

    private:
        void listenKeys();

        std::atomic<bool> isListening_;
        std::thread listeningThread_;

        gpioISRFuncEx_t callback_;
        void* internalData_;
        int edge_;

        std::map<uint8_t, uint8_t> dictionary_;
#endif
    };
}

#endif