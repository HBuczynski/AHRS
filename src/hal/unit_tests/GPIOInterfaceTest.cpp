#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../include/GPIOInterface.h"

using namespace std;
using namespace hardware;

BOOST_AUTO_TEST_SUITE( gpio_test )

    BOOST_AUTO_TEST_CASE( reading )
    {
        GPIO gpio;

        gpio.pinNumber = 23;

        GPIOInterface anInterface(gpio);

        while(1)
        {
            cout << anInterface.pinRead() << endl;
        }

    }

BOOST_AUTO_TEST_SUITE_END()
