#define BOOST_TEST_MODULE MeasuringDataTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../MeasuringDataFactory.h"
#include "../ImuData.h"
#include "../GpsData.h"
#include "../FlightData.h"

#include <string>


using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( data )

    BOOST_AUTO_TEST_CASE( imuDataBuilder )
    {
        ImuData data(12);
        MeasuringDataFactory factory;

        auto commandFromVec = static_pointer_cast<ImuData, MeasuringData>(factory.createCommand(data.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameType() == data.getFrameType());
        BOOST_CHECK( commandFromVec->getMeasuringType() == data.getMeasuringType());
        BOOST_CHECK( commandFromVec->getFrameBytes() == data.getFrameBytes());
        BOOST_CHECK( commandFromVec->getSystemVersion() == data.getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == data.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == data.getName());
    }

    BOOST_AUTO_TEST_CASE( gpsDataBuilder )
    {
        GpsData data;
        MeasuringDataFactory factory;

        auto commandFromVec = static_pointer_cast<GpsData, MeasuringData>(factory.createCommand(data.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameType() == data.getFrameType());
        BOOST_CHECK( commandFromVec->getMeasuringType() == data.getMeasuringType());
        BOOST_CHECK( commandFromVec->getFrameBytes() == data.getFrameBytes());
        BOOST_CHECK( commandFromVec->getSystemVersion() == data.getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == data.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == data.getName());
    }

    BOOST_AUTO_TEST_CASE( flightData )
    {
        FlightMeasurements measurements = {5.67, 5.67, 5.67, 5.67, 5.67, 5.67, 5.67};
        FlightData data(measurements);
        MeasuringDataFactory factory;

        auto commandFromVec = static_pointer_cast<FlightData, MeasuringData>(factory.createCommand(data.getFrameBytes()));

        bool isSuccess = true;
        const auto measurementsFromCommand = commandFromVec->getMeasurements();

        isSuccess = isSuccess && (measurements.altitude = measurementsFromCommand.altitude);
        isSuccess = isSuccess && (measurements.groundSpeed = measurementsFromCommand.groundSpeed);
        isSuccess = isSuccess && (measurements.heading = measurementsFromCommand.heading);
        isSuccess = isSuccess && (measurements.latitude = measurementsFromCommand.latitude);
        isSuccess = isSuccess && (measurements.longitude = measurementsFromCommand.longitude);
        isSuccess = isSuccess && (measurements.turnCoordinator = measurementsFromCommand.turnCoordinator);
        isSuccess = isSuccess && (measurements.verticalSpeed = measurementsFromCommand.verticalSpeed);

        BOOST_CHECK( commandFromVec->getFrameType() == data.getFrameType());
        BOOST_CHECK( commandFromVec->getMeasuringType() == data.getMeasuringType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == data.getSystemVersion());
        BOOST_CHECK( commandFromVec->getFrameBytes() == data.getFrameBytes());
        BOOST_CHECK(  isSuccess == true);
        BOOST_CHECK( commandFromVec->getDataSize() == data.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == data.getName());
    }


BOOST_AUTO_TEST_SUITE_END()

