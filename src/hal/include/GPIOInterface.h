#ifndef SWITCHES_DRIVER_H
#define SWITCHES_DRIVER_H

#include <functional>

namespace hardware
{

    struct GPIO
    {
        uint8_t pinNumber;
        uint8_t pinMode;
        uint8_t pushPullMode;
    };

    class GPIOInterface
    {
    public:
        GPIOInterface(GPIO gpio);
        ~GPIOInterface();

        bool initialize() const;

        void pinWrite(int state);
        int pinRead() const;

        void activateRaisingInterrupt(std::function<void()> callback);
        void activateFallingInterrupt(std::function<void()> callback);

    private:

        GPIO gpio_;
        std::function< void() > raisingInterruptCallback_;
        std::function< void() > fallingInterruptCallback_;
    };
}

#endif