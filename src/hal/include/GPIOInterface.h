#ifndef SWITCHES_DRIVER_H
#define SWITCHES_DRIVER_H

#include <functional>

namespace hardware
{
    // to do: pull up & pull down

    enum GPIOState : uint8_t
    {
        HIGH = 0x10,
        LOW = 0x20
    };

    enum GPIOMode : uint8_t
    {
        INPUT = 0x10,
        OUTPUT = 0x20
    };

    enum InterruptEdge : uint8_t
    {
        RISING = 0x10,
        FALLING = 0x20,
        BOTH = 0x30
    };

    struct GPIO
    {
        uint8_t pinNumber;
        GPIOState state;
        GPIOMode mode;
        InterruptEdge interrupt;
    };

    class GPIOInterface
    {
    public:
        GPIOInterface(GPIO gpio);
        ~GPIOInterface();

        void initialize();

        void activateInterrupt(std::function< void() >  callback);
        GPIOState getState();
        uint8_t getPinNumber();
        GPIOMode getMode();

    private:
        void interruptHandler();

    private:
        GPIO gpio_;
        std::function< void() > callback_;
    };
}

#endif