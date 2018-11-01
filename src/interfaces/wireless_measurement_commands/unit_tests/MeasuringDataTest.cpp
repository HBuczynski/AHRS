#define BOOST_TEST_MODULE MeasuringDataTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../ImuData.h"
#include "../GpsData.h"
#include "../FlightData.h"

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
        FlightMeasurements measurements = {5.67, 5.67, 5.67, 5.67, 5.67, 5.67, 5.67};
        FlightData data(measurements);
        data.getFrameBytes();

        bool isSuccess = true;
        const auto measurementsFromCommand = data.getMeasurements();

        isSuccess = isSuccess && (measurements.altitude = measurementsFromCommand.altitude);
        isSuccess = isSuccess && (measurements.groundSpeed = measurementsFromCommand.groundSpeed);
        isSuccess = isSuccess && (measurements.heading = measurementsFromCommand.heading);
        isSuccess = isSuccess && (measurements.latitude = measurementsFromCommand.latitude);
        isSuccess = isSuccess && (measurements.longitude = measurementsFromCommand.longitude);
        isSuccess = isSuccess && (measurements.turnCoordinator = measurementsFromCommand.turnCoordinator);
        isSuccess = isSuccess && (measurements.verticalSpeed = measurementsFromCommand.verticalSpeed);

        BOOST_CHECK( FrameType::MEASUREMENT_DATA == data.getFrameType());
        BOOST_CHECK( MeasuringType::FLIGHT_DATA == data.getMeasuringType());
        BOOST_CHECK( 1 == data.getSystemVersion());
        BOOST_CHECK(  isSuccess == true);
        BOOST_CHECK( (sizeof(MeasuringType::GPS) + sizeof(measurements)) == data.getDataSize());
        BOOST_CHECK( "FlightData" == data.getName());
    }


BOOST_AUTO_TEST_SUITE_END()
