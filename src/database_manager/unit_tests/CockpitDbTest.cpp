#define BOOST_TEST_MODULE ServerTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CockpitDb.h"

using namespace database;

BOOST_AUTO_TEST_SUITE( cockpit )

        BOOST_AUTO_TEST_CASE( test_int )
        {
            CockpitDb cockpitDb("cockpitExample.db");
            cockpitDb.openDb();
            cockpitDb.createTable();

            cockpitDb.insertHASH(282397);

            CockpitNetwork cockpitNetwork;
            cockpitNetwork.timestamp = 92834;
            cockpitNetwork.bandwith = 234.56;
            cockpitNetwork.networkMode = 9873;
            cockpitNetwork.networkNumber = 3;

            cockpitDb.insertCockpitNetwork(cockpitNetwork);

            CockpitProperties cockpitProperties;
            cockpitProperties.timestamp = 233;
            cockpitProperties.core1 = 198.09;
            cockpitProperties.core2 = 298.09;
            cockpitProperties.core3 = 398.09;
            cockpitProperties.core4 = 298.09;
            cockpitProperties.power = 221.122;
            cockpitProperties.temperature = 67.39;

            cockpitDb.insertCockpitProperties(cockpitProperties);

            FlightMeasurements flightMeasurements;
            flightMeasurements.timestamp = 233;
            flightMeasurements.slipSkid = 67.09;
            flightMeasurements.turnCoordinator = 908.23;
            flightMeasurements.latitudeDirection = 'N';
            flightMeasurements.verticalSpeed = 87.54;
            flightMeasurements.groundSpeed = 213.088;
            flightMeasurements.machNo = 0.9;
            flightMeasurements.pressure = 998.456;
            flightMeasurements.altitude = 7864.98;
            flightMeasurements.heading = 345.89;
            flightMeasurements.pitch = 67.89;
            flightMeasurements.roll = 76.56;
            flightMeasurements.longitudeDirection = 'E';
            flightMeasurements.longitude = 98.788;
            flightMeasurements.latitude = 765.89;

            cockpitDb.insertFlightMeasurement(flightMeasurements);
        }

BOOST_AUTO_TEST_SUITE_END()

