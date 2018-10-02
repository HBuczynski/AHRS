#ifndef SWITCHES_DRIVER_H
#define SWITCHES_DRIVER_H

#include <functional>

namespace hardware
{
    enum class GPIOMode : uint8_t
    {
        IN = 0x01,
        OUT = 0x02
    };

    enum class GPIOPullMode : uint8_t
    {
        DOWN = 0x01,
        UP = 0x02
    };

    struct GPIO
    {
        uint8_t pinNumber;
        GPIOMode pinMode;
        GPIOPullMode pushPullMode;
    };

    class GPIOInterface
    {
    public:
        GPIOInterface(GPIO gpio);
        ~GPIOInterface();

        bool initialize() const;

        void pinWrite(int state);
        int pinRead() const;

    protected:
        GPIO gpio_;

    private:
        uint8_t getMode(GPIOMode mode) const;
        uint8_t getPullMode(GPIOPullMode pullMode) const;

    };
}

#endif