#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "switches/SwitchHandle.h"

#include <iostream>

using namespace std;
using namespace utility;
using namespace hardware;
using namespace peripherals;

BOOST_AUTO_TEST_SUITE( test_multiply )

    BOOST_AUTO_TEST_CASE( test_int )
    {
        Logger &logger = Logger::getInstance("SWITCH_TEST");

        InitLogStructure struc;
        struc.debugLog = true;
        struc.errroLog = true;
        struc.informationLog = true;
        struc.warningLog = true;
        struc.writeLogsInSeparetFiles = true;
        struc.writeOnConsole = true;

        logger.initLogger(struc);

        GPIO gpio;

        gpio.pinNumber = 23;
        gpio.pinMode = GPIOMode::IN;
        gpio.pushPullMode = GPIOPullMode::DOWN;

        bool ok = true;

        {
            SwitchHandle handle(gpio, SwitchCode::FOURTH_SWITCH);

            function<void()> pressedSwitchCallback = [&]() { ok = false; cout << "Pressed Button." << endl; };
            function<void(SwitchCode, SwitchState)> errorCallback = [](SwitchCode code, SwitchState state) {
                cout << "Error:: State -- " << (int) state << "  Code --" << (int) code << endl;
            };

            handle.initializeCallbacks(pressedSwitchCallback, errorCallback);

            while (ok)
            {}

            ok = true;
        }

        SwitchHandle handle(gpio, SwitchCode::FOURTH_SWITCH);

        function<void()> pressedSwitchCallback = []() { cout << "Pressed Button." << endl; };
        function<void(SwitchCode, SwitchState)> errorCallback = [](SwitchCode code, SwitchState state) {
            cout << "Error:: State -- " << (int) state << "  Code --" << (int) code << endl;
        };

        handle.initializeCallbacks(pressedSwitchCallback, errorCallback);

        while (1)
        {}

    }

BOOST_AUTO_TEST_SUITE_END()


