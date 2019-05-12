#define BOOST_TEST_MODULE NMEATest

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../include/GPSAdafruitInterface.h"


#include <thread>
#include <iostream>

using namespace std;
using namespace gps;
using namespace chrono;

BOOST_AUTO_TEST_SUITE( nmea_telemetry )

    BOOST_AUTO_TEST_CASE( get_gps )
    {
//        string gpgga = "$GPGGA,204423.000,5213.1755,N,02101.4210,E,2,07,1.32,135.1,M,39.0,M,0000,0000*61";
        //$GPGGA,085600.916,,,,,0,02,,,M,,M,,*7F
//        string gprmc = "$GPRMC,204423.000,A,5213.1755,N,02101.4210,E,0.25,256.25,150319,,,D*60";
//
//        GPSData data{0};
//
//        NMEAParser::parseGPGGAData(gpgga, data);
//        NMEAParser::parseGPRMCData(gprmc, data);
        GPSAdafruitInterface adafruitInterface("/dev/ttyS0");
        adafruitInterface.initialize();

        while (adafruitInterface.getStatus() != GPSStatus::FIXED) {
            this_thread::sleep_for(std::chrono::milliseconds(2));
        }

        cout << "DONE" << endl;

//        adafruitInterface.startAcq();

//        while (1)
//        {
//            auto data = adafruitInterface.getData();

//            cout << (int) data.latitude << endl;
//            cout << (char) data.latitudeDirection << endl;
//            cout << (int) data.longitude << endl;
//            cout << (char) data.longitudeDirection << endl;
//            cout << (int) data.numberOfSatellites << endl;
//            cout << (int) data.fixQuality << endl;
//        }
    }

BOOST_AUTO_TEST_SUITE_END()


