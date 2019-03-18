#define BOOST_TEST_MODULE NMEATest

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../NMEAParser.h"

#include <thread>
#include <iostream>

using namespace std;
using namespace gps;
using namespace chrono;

BOOST_AUTO_TEST_SUITE( nmea_telemetry )

    BOOST_AUTO_TEST_CASE( get_gps )
    {
        string gpgga = "$GPGGA,204423.000,5213.1755,N,02101.4210,E,2,07,1.32,135.1,M,39.0,M,0000,0000*61";
        string gprmc = "$GPRMC,204423.000,A,5213.1755,N,02101.4210,E,0.25,256.25,150319,,,D*60";

        GPSData data;

        NMEAParser::parseGPGGAData(gpgga, data);

        cout << "Start" << endl;
    }

BOOST_AUTO_TEST_SUITE_END()


