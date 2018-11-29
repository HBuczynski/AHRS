#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../PlaneOrientation.h"

#include <thread>
#include <iostream>

using namespace std;
using namespace chrono;
using namespace utility;
using namespace telemetry;

BOOST_AUTO_TEST_SUITE( test_telemetry )

    BOOST_AUTO_TEST_CASE( get_position )
    {
        Logger &logger = Logger::getInstance("TELEMETRY_TEST");

        InitLogStructure struc;
        struc.debugLog = true;
        struc.errroLog = true;
        struc.informationLog = false;
        struc.warningLog = true;
        struc.writeLogsInSeparetFiles = true;
        struc.writeOnConsole = true;

        logger.initLogger(struc);

        PlaneOrientation planeOrientation;
        planeOrientation.initDataAcquisition();

        while(true)
        {
            auto startTime_ = std::chrono::system_clock::now();
            planeOrientation.readData();

            auto currentTime = std::chrono::high_resolution_clock::now();
            auto timeSinceStart =  std::chrono::duration_cast<microseconds>(currentTime - startTime_).count();

            cout << "Time: " << timeSinceStart << endl;
//            cout << "Roll: " << planeOrientation.getRoll() << "\t";
//            cout << "Pitch: " << planeOrientation.getPitch() << "\t";
//            cout << "Yaw: " << planeOrientation.getYaw() << "\t";
//            cout << endl;
        }

    }

BOOST_AUTO_TEST_SUITE_END()


