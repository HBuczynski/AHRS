#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../SwitcheHandle.h"

#include <iostream>

using namespace std;
using namespace hardware;
using namespace peripherals;

BOOST_AUTO_TEST_SUITE( test_multiply )

    BOOST_AUTO_TEST_CASE( test_int )
    {
        GPIO gpio;

        gpio.pinNumber = 23;
        gpio.pinMode = GPIOMode::IN;
        gpio.pushPullMode = GPIOPullMode::DOWN;

        SwitcheHandle handle(gpio, SwitchesCode::FOURTH_SWITCH);

        function< void() > pressedSwitchCallback = []() { cout << "Pressed Button." << endl;};
        function< void(SwitchesCode) > errorCallback = [](SwitchesCode code) { cout << "Error " << (int)code << endl;};

        handle.initializeCallbacks(pressedSwitchCallback, errorCallback);

        while(1)
        { }
    }

BOOST_AUTO_TEST_SUITE_END()


