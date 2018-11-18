#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../PlaneOrientation.h"

#include <thread>
#include <iostream>

using namespace std;
using namespace utility;
using namespace telemetry;

BOOST_AUTO_TEST_SUITE( test_telemetry )

    BOOST_AUTO_TEST_CASE( get_position )
    {
        Logger &logger = Logger::getInstance("TELEMETRY_TEST");

        InitLogStructure struc;
        struc.debugLog = true;
        struc.errroLog = true;
        struc.informationLog = true;
        struc.warningLog = true;
        struc.writeLogsInSeparetFiles = true;
        struc.writeOnConsole = true;

        logger.initLogger(struc);

        PlaneOrientation planeOrientation;
        planeOrientation.initDataAcquisition();

        while(true)
        {
            planeOrientation.readData();

            cout << "Roll: " << planeOrientation.getRoll() << endl;
            cout << "Pitch: " << planeOrientation.getPitch() << endl;
            cout << "Yaw: " << planeOrientation.getYaw() << endl;
            cout << endl;

            std::this_thread::sleep_for (std::chrono::milliseconds(100));
        }

    }

BOOST_AUTO_TEST_SUITE_END()


