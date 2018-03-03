#ifndef SWITCHES_DRIVER_H
#define SWITCHES_DRIVER_H

#include <functional>

namespace hardware
{
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

    class GPIOInterface
    {
    public:
        GPIOInterface(uint8_t pinNumber, GPIOMode mode);
        ~GPIOInterface();

        void activateInterrupt(std::function< void() >  callback, InterruptEdge edge);

        GPIOState getState();
        uint8_t getPinNumber();
        GPIOMode getMode();

    private:
        void interruptHandler();

    private:
        GPIOState state_;
        uint8_t pinNumber_;
        GPIOMode mode_;
    };
}

#endif