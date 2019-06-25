#define BOOST_TEST_MODULE ResponseFactory

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../ResponseFactory.h"
#include "../DataResponse.h"
#include "../AckResponse.h"
#include "../BITsResponse.h"
#include "../CalibratingStatusResponse.h"
#include "../PlanesDatasetResponse.h"

#include <string>

using namespace std;
using namespace communication;

bool compareNames(const char* name1, const char* name2, uint8_t sizeOfNames)
{
    for (uint8_t i = 0; i < sizeOfNames; ++i)
    {
        if(name1[i] != name2[i])
        {
            return false;
        }
    }

    return true;
}

BOOST_AUTO_TEST_SUITE( test )

    BOOST_AUTO_TEST_CASE( dataResponseBuilder )
    {
        string data("Temp data");
        DataResponse response(data);
        ResponseFactory factory;

        auto responseFromVec = static_pointer_cast<DataResponse, Response>(factory.createCommand(response.getFrameBytes()));

        BOOST_CHECK( responseFromVec->getFrameType() == response.getFrameType());
        BOOST_CHECK( responseFromVec->getData() == response.getData());
        BOOST_CHECK( responseFromVec->getResponseType() == response.getResponseType());
        BOOST_CHECK( responseFromVec->getFrameBytes() == response.getFrameBytes());
        BOOST_CHECK( responseFromVec->getSystemVersion() == response.getSystemVersion());
        BOOST_CHECK( responseFromVec->getDataSize() == response.getDataSize());
        BOOST_CHECK( responseFromVec->getName() == response.getName());
    }

    BOOST_AUTO_TEST_CASE( ackResponseBuilder )
    {
        AckResponse response(AckType::OK);
        ResponseFactory factory;

        auto responseFromVec = static_pointer_cast<AckResponse, Response>(factory.createCommand(response.getFrameBytes()));

        BOOST_CHECK( responseFromVec->getFrameType() == response.getFrameType());
        BOOST_CHECK( responseFromVec->getAckType() == response.getAckType());
        BOOST_CHECK( responseFromVec->getResponseType() == response.getResponseType());
        BOOST_CHECK( responseFromVec->getFrameBytes() == response.getFrameBytes());
        BOOST_CHECK( responseFromVec->getSystemVersion() == response.getSystemVersion());
        BOOST_CHECK( responseFromVec->getDataSize() == response.getDataSize());
        BOOST_CHECK( responseFromVec->getName() == response.getName());
    }

    BOOST_AUTO_TEST_CASE( calibratingStatusBuilder )
    {
        uint8_t mode = 0;
        CalibrationConfiguration calibration;
        calibration.progress = 23;
        calibration.accelerometer.maxX = 76.34;
        calibration.accelerometer.minX = 126.34;
        calibration.magnetometer.maxX = 76.34;
        calibration.magnetometer.minX = 126.34;
        calibration.accelerometer.maxZ = 769.34;
        calibration.accelerometer.minZ = 3426.34;
        calibration.ellipsoid.quadrant_32 = 3426;

        CalibratingStatusResponse response(calibration, mode);

        ResponseFactory factory;

        auto responseFromVec = static_pointer_cast<CalibratingStatusResponse, Response>(factory.createCommand(response.getFrameBytes()));

        const auto newCallibration = responseFromVec->getCalibrationConfiguration();

        BOOST_CHECK( responseFromVec->getFrameType() == response.getFrameType());
        BOOST_CHECK( calibration.progress == newCallibration.progress);
        BOOST_CHECK( calibration.accelerometer.maxX == newCallibration.accelerometer.maxX);
        BOOST_CHECK( calibration.accelerometer.minX == newCallibration.accelerometer.minX);
        BOOST_CHECK( calibration.magnetometer.maxX == newCallibration.magnetometer.maxX);
        BOOST_CHECK( calibration.magnetometer.minX == newCallibration.magnetometer.minX);
        BOOST_CHECK( calibration.accelerometer.maxZ == newCallibration.accelerometer.maxZ);
        BOOST_CHECK( calibration.accelerometer.minZ == newCallibration.accelerometer.minZ);
        BOOST_CHECK( calibration.ellipsoid.quadrant_32 == newCallibration.ellipsoid.quadrant_32);
        BOOST_CHECK( responseFromVec->getResponseType() == response.getResponseType());
        BOOST_CHECK( responseFromVec->getFrameBytes() == response.getFrameBytes());
        BOOST_CHECK( responseFromVec->getSystemVersion() == response.getSystemVersion());
        BOOST_CHECK( responseFromVec->getDataSize() == response.getDataSize());
        BOOST_CHECK( responseFromVec->getName() == response.getName());
    }

    BOOST_AUTO_TEST_CASE( planesDatasetBuilder )
    {
        ResponseFactory factory;
        string planes = "Boeing,Trolo";

        PlanesDatasetResponse command(planes);
        auto commandFromVec = static_pointer_cast<PlanesDatasetResponse, Response>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getFrameType() == command.getFrameType());
        BOOST_CHECK( commandFromVec->getResponseType() == command.getResponseType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == command.getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
        BOOST_CHECK(commandFromVec->getDataset() == command.getDataset());
    }

    BOOST_AUTO_TEST_CASE( bitsBuilder )
    {
        ResponseFactory factory;
        BitsInformation info;
        info.communication = 98;
        info.gps = 123;

        BITsResponse command(info);
        auto commandFromVec = static_pointer_cast<BITsResponse, Response>(factory.createCommand(command.getFrameBytes()));

        const auto tempInfo = commandFromVec->getBits();

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getFrameType() == command.getFrameType());
        BOOST_CHECK( commandFromVec->getResponseType() == command.getResponseType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == command.getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
        BOOST_CHECK(info.communication == tempInfo.communication);
        BOOST_CHECK(info.gps == tempInfo.gps);
    }

BOOST_AUTO_TEST_SUITE_END()

