#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../include/Switch.h"
#include "../../../3rd_party/PIGPIO/pigpio.h"

using namespace std;
using namespace hardware;

BOOST_AUTO_TEST_SUITE( gpio_test )

    BOOST_AUTO_TEST_CASE( reading )
    {
        GPIO gpio;

        gpio.pinNumber = 23;
        gpio.pinMode = GPIOMode::IN;
        gpio.pushPullMode = GPIOPullMode::DOWN;

        Switch aSwitch(gpio);

//        aSwitch.registerHandler(FALLING_EDGE);
//        aSwitch.registerHandler(RISING_EDGE);

        while(1)
        {

        }

    }

BOOST_AUTO_TEST_SUITE_END()
