#ifndef AHRS_PIGPIOHANDLER_H
#define AHRS_PIGPIOHANDLER_H

#include <atomic>

namespace hardware
{
    class PIGPIOInitializer
    {
    public:
        PIGPIOInitializer();
        ~PIGPIOInitializer();

        static void initialize();

        static void terminate();

    private:
        static std::atomic<bool> initializerFlag_;
    };
}

#endif //AHRS_PIGPIOHANDLER_H
