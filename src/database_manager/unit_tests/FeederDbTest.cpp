#define BOOST_TEST_MODULE ServerTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../FeederDb.h"

using namespace database;

BOOST_AUTO_TEST_SUITE( feeder )

BOOST_AUTO_TEST_CASE( test_int )
        {
                FeederDb feederDb("feederExample.db");

                feederDb.openDb();
                feederDb.createTable();

                IMUData data;
                data.roll = 46.3;
                data.pitch = 76.34;
                data.yaw = 53.23;
                data.accelZ = 764.34;
                data.accelY = 762.232;
                data.accelX = 6522.90;
                data.timestamp = 12565632;
                feederDb.insertIMU(data);

                GPSData gpsData;
                gpsData.course = 22223.45;
                gpsData.groundSpeed = 22384.90;
                gpsData.receiverWarning = 'A';
                gpsData.numberOfSatellites = 9;
                gpsData.fixQuality = 0;
                gpsData.longitude = 13.405665443;
                gpsData.latitude = 122.7067867;
                gpsData.altitude =345.89;
                gpsData.longitudeDirection = 'N';
                gpsData.latitudeDirection = 'E';
                gpsData.timestamp = 232323;
                feederDb.insertGPS(gpsData);

                FeederProperties properties;
                properties.timestamp = 126527434;
                properties.mode = 23;
                properties.bandwith = 2.46;
                properties.temperature  = 78.09;
                properties.power = 100.01;
                properties.core1 = 589.90;
                properties.core2 = 489.90;
                properties.core3 = 389.90;
                properties.core4 = 289.90;

                feederDb.insertFeederProperties(properties);
                feederDb.insertGPS(gpsData);

                feederDb.insertHASH(127864356);
        }

BOOST_AUTO_TEST_SUITE_END()

