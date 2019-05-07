#define BOOST_TEST_MODULE MeasuringDataTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../ImuData.h"
#include "../GpsData.h"
#include "../FeederData.h"

#include <string>

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( data )

    BOOST_AUTO_TEST_CASE( imuData )
    {
        ImuData data(12);
        data.getFrameBytes();

        BOOST_CHECK( FrameType::MEASUREMENT_DATA == data.getFrameType());
        BOOST_CHECK( MeasuringType::IMU == data.getMeasuringType());
        BOOST_CHECK( 1 == data.getSystemVersion());
        BOOST_CHECK( (sizeof(MeasuringType::IMU)) == data.getDataSize());
        BOOST_CHECK( "ImuData" == data.getName());
    }

    BOOST_AUTO_TEST_CASE( gpsData )
    {
        GpsData data;
        data.getFrameBytes();

        BOOST_CHECK( FrameType::MEASUREMENT_DATA == data.getFrameType());
        BOOST_CHECK( MeasuringType::GPS == data.getMeasuringType());
        BOOST_CHECK( 1 == data.getSystemVersion());
        BOOST_CHECK( (sizeof(MeasuringType::GPS)) == data.getDataSize());
        BOOST_CHECK( "GpsData" == data.getName());
    }

    BOOST_AUTO_TEST_CASE( flightData )
    {
        FeederGeneralData measurements;

        measurements.flightMeasurements.altitude = 5.67;
        measurements.flightMeasurements.groundSpeed = 5.67;
        measurements.flightMeasurements.heading = 5.67;
        measurements.flightMeasurements.latitude = 5.67;
        measurements.flightMeasurements.longitude = 5.67;
        measurements.flightMeasurements.turnCoordinator = 5.67;
        measurements.flightMeasurements.verticalSpeed = 5.67;

        FeederData data(measurements);
        data.getFrameBytes();

        bool isSuccess = true;
        const auto measurementsFromCommand = data.getMeasurements();

        isSuccess = isSuccess && (measurements.flightMeasurements.altitude = measurementsFromCommand.flightMeasurements.altitude);
        isSuccess = isSuccess && (measurements.flightMeasurements.groundSpeed = measurementsFromCommand.flightMeasurements.groundSpeed);
        isSuccess = isSuccess && (measurements.flightMeasurements.heading = measurementsFromCommand.flightMeasurements.heading);
        isSuccess = isSuccess && (measurements.flightMeasurements.latitude = measurementsFromCommand.flightMeasurements.latitude);
        isSuccess = isSuccess && (measurements.flightMeasurements.longitude = measurementsFromCommand.flightMeasurements.longitude);
        isSuccess = isSuccess && (measurements.flightMeasurements.turnCoordinator = measurementsFromCommand.flightMeasurements.turnCoordinator);
        isSuccess = isSuccess && (measurements.flightMeasurements.verticalSpeed = measurementsFromCommand.flightMeasurements.verticalSpeed);

        BOOST_CHECK( FrameType::MEASUREMENT_DATA == data.getFrameType());
        BOOST_CHECK( MeasuringType::FLIGHT_DATA == data.getMeasuringType());
        BOOST_CHECK( 1 == data.getSystemVersion());
        BOOST_CHECK(  isSuccess == true);
        BOOST_CHECK( (sizeof(MeasuringType::GPS) + sizeof(measurements)) == data.getDataSize());
        BOOST_CHECK( "FlightData" == data.getName());
    }


BOOST_AUTO_TEST_SUITE_END()
