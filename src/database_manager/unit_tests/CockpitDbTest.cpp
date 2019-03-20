#define BOOST_TEST_MODULE ServerTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CockpitDb.h"

using namespace database;

BOOST_AUTO_TEST_SUITE( cockpit )

        BOOST_AUTO_TEST_CASE( test_int )
        {
            CockpitDb cockpitDb("cockpitExample.db");
            cockpitDb.initialize();

            CockpitNetwork cockpitNetwork;
            cockpitNetwork.timestamp = "12.34.56";
            cockpitNetwork.bandwith = 234.56;
            cockpitNetwork.networkMode = "MASTER";
            cockpitNetwork.networkNumber = "2";

            cockpitDb.insertHASH(282397);
            cockpitDb.insertCockpitNetwork(cockpitNetwork);

            CockpitProperties cockpitProperties;
            cockpitProperties.timestamp = "12:45:09";
            cockpitProperties.processorConsumption = 98.09;
            cockpitProperties.power = 221.122;
            cockpitProperties.temperature = 67.39;

            cockpitDb.insertCockpitProperties(cockpitProperties);

            FlightMeasurements flightMeasurements;
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

