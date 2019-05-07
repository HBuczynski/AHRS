#define BOOST_TEST_MODULE MeasuringDataTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../MeasuringDataFactory.h"
#include "../ImuData.h"
#include "../GpsData.h"
#include "../FeederData.h"

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
        FeederGeneralData measurements;

        measurements.flightMeasurements.altitude = 5.67;
        measurements.flightMeasurements.groundSpeed = 5.67;
        measurements.flightMeasurements.heading = 5.67;
        measurements.flightMeasurements.latitude = 5.67;
        measurements.flightMeasurements.longitude = 5.67;
        measurements.flightMeasurements.turnCoordinator = 5.67;
        measurements.flightMeasurements.verticalSpeed = 5.67;

        FeederData data(measurements);
        MeasuringDataFactory factory;

        auto commandFromVec = static_pointer_cast<FeederData, MeasuringData>(factory.createCommand(data.getFrameBytes()));

        bool isSuccess = true;
        const auto measurementsFromCommand = commandFromVec->getMeasurements();

        isSuccess = isSuccess && (measurements.flightMeasurements.altitude = measurementsFromCommand.flightMeasurements.altitude);
        isSuccess = isSuccess && (measurements.flightMeasurements.groundSpeed = measurementsFromCommand.flightMeasurements.groundSpeed);
        isSuccess = isSuccess && (measurements.flightMeasurements.heading = measurementsFromCommand.flightMeasurements.heading);
        isSuccess = isSuccess && (measurements.flightMeasurements.latitude = measurementsFromCommand.flightMeasurements.latitude);
        isSuccess = isSuccess && (measurements.flightMeasurements.longitude = measurementsFromCommand.flightMeasurements.longitude);
        isSuccess = isSuccess && (measurements.flightMeasurements.turnCoordinator = measurementsFromCommand.flightMeasurements.turnCoordinator);
        isSuccess = isSuccess && (measurements.flightMeasurements.verticalSpeed = measurementsFromCommand.flightMeasurements.verticalSpeed);

        BOOST_CHECK( commandFromVec->getFrameType() == data.getFrameType());
        BOOST_CHECK( commandFromVec->getMeasuringType() == data.getMeasuringType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == data.getSystemVersion());
        BOOST_CHECK( commandFromVec->getFrameBytes() == data.getFrameBytes());
        BOOST_CHECK(  isSuccess == true);
        BOOST_CHECK( commandFromVec->getDataSize() == data.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == data.getName());
    }


BOOST_AUTO_TEST_SUITE_END()

