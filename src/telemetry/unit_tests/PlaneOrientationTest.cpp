#define BOOST_TEST_MODULE PlaneOrientationTest

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
//#include "../PlaneOrientationHandler.h"

#include <thread>
#include <iostream>

using namespace std;
using namespace chrono;

BOOST_AUTO_TEST_SUITE( test_telemetry )

    BOOST_AUTO_TEST_CASE( get_position )
    {
//        Logger &logger = Logger::getInstance("TELEMETRY_TEST");

//        InitLogStructure struc;
//        struc.debugLog = true;
//        struc.errroLog = true;
//        struc.informationLog = true;
//        struc.warningLog = true;
//        struc.writeLogsInSeparetFiles = true;
//        struc.writeOnConsole = true;

//        logger.initLogger(struc);

//        PlaneOrientationHandler planeOrientation;
//        std::string temp = "temp";
//        planeOrientation.initDataAcquisition(temp);

//        while(true)
//        {
//            planeOrientation.readData();


//            //cout << "Time: " << timeSinceStart << endl;
////            cout << "Roll: " << planeOrientation.getRoll() << "\t";
////            cout << "Pitch: " << planeOrientation.getPitch() << "\t";
////            cout << "Yaw: " << planeOrientation.getYaw() << "\t";
////            cout << endl;
//        }

    }

BOOST_AUTO_TEST_SUITE_END()


