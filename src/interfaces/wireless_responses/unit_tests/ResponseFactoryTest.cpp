#define BOOST_TEST_MODULE ResponseFactory

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../ResponseFactory.h"
#include "../DataResponse.h"
#include "../AckResponse.h"
#include "../CalibratingStatusResponse.h"
#include "../PlanesDatasetResponse.h"

#include <string>

using namespace std;
using namespace communication;

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
        const auto status = CalibrationStatus::IN_THE_PROCESS;
        CalibratingStatusResponse response(status);

        ResponseFactory factory;

        auto responseFromVec = static_pointer_cast<CalibratingStatusResponse, Response>(factory.createCommand(response.getFrameBytes()));

        BOOST_CHECK( responseFromVec->getFrameType() == response.getFrameType());
        BOOST_CHECK( responseFromVec->getCalibrationStatus() == response.getCalibrationStatus());
        BOOST_CHECK( responseFromVec->getResponseType() == response.getResponseType());
        BOOST_CHECK( responseFromVec->getFrameBytes() == response.getFrameBytes());
        BOOST_CHECK( responseFromVec->getSystemVersion() == response.getSystemVersion());
        BOOST_CHECK( responseFromVec->getDataSize() == response.getDataSize());
        BOOST_CHECK( responseFromVec->getName() == response.getName());
    }

    BOOST_AUTO_TEST_CASE( planesDatasetBuilder )
    {
        vector<string> dataset;
        string plane_1 = "boeing";
        dataset.push_back(plane_1);
        string plane_2 = "bombardier4";
        dataset.push_back(plane_2);
        string plane_3 = "boeing_kk5";
        dataset.push_back(plane_3);
        string plane_4 = "airbus_11";
        dataset.push_back(plane_4);
        PlanesDatasetResponse response(dataset);

        ResponseFactory factory;

        auto responseFromVec = static_pointer_cast<PlanesDatasetResponse, Response>(factory.createCommand(response.getFrameBytes()));

        BOOST_CHECK( responseFromVec->getFrameType() == response.getFrameType());
        BOOST_CHECK( responseFromVec->getDataset() == response.getDataset());
        BOOST_CHECK( responseFromVec->getResponseType() == response.getResponseType());
        BOOST_CHECK( responseFromVec->getFrameBytes() == response.getFrameBytes());
        BOOST_CHECK( responseFromVec->getSystemVersion() == response.getSystemVersion());
        BOOST_CHECK( responseFromVec->getDataSize() == response.getDataSize());
        BOOST_CHECK( responseFromVec->getName() == response.getName());
    }

BOOST_AUTO_TEST_SUITE_END()

