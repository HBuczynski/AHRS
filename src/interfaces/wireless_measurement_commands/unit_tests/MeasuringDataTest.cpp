#define BOOST_TEST_MODULE MeasuringDataTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../ImuData.h"
#include "../GpsData.h"

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


BOOST_AUTO_TEST_SUITE_END()
