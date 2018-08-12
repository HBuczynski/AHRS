#define BOOST_TEST_MODULE ResponsesTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../DataResponse.h"
#include "../AckResponse.h"
#include "../CalibratingStatusResponse.h"
#include "../PlanesDatasetResponse.h"

#include <string>

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( data )

    BOOST_AUTO_TEST_CASE( dataResponse )
    {
        string data("Temp data");
        DataResponse response(data);
        response.getFrameBytes();

        BOOST_CHECK( FrameType::RESPONSE == response.getFrameType());
        BOOST_CHECK( ResponseType::DATA == response.getResponseType());
        BOOST_CHECK( data == response.getData());
        BOOST_CHECK( 1 == response.getSystemVersion());
        BOOST_CHECK( (sizeof(ResponseType::DATA)+data.size()+sizeof(END_STRING_IN_FRAME)) == response.getDataSize());
        BOOST_CHECK( "DataResponse" == response.getName());
    }

    BOOST_AUTO_TEST_CASE( ackResponse )
    {
        AckResponse response(AckType::OK);
        response.getFrameBytes();

        BOOST_CHECK( FrameType::RESPONSE == response.getFrameType());
        BOOST_CHECK( ResponseType::ACK == response.getResponseType());
        BOOST_CHECK( AckType::OK == response.getAckType());
        BOOST_CHECK( 1 == response.getSystemVersion());
        BOOST_CHECK( (sizeof(ResponseType::ACK) + sizeof(AckType::FAIL)) == response.getDataSize());
        BOOST_CHECK( "AckResponse" == response.getName());
    }

    BOOST_AUTO_TEST_CASE( calibratingStatus )
    {
        const auto status = CalibrationStatus::IN_THE_PROCESS;
        CalibratingStatusResponse response(status);
        response.getFrameBytes();

        BOOST_CHECK( FrameType::RESPONSE == response.getFrameType());
        BOOST_CHECK( ResponseType::CALIBRATING_STATUS == response.getResponseType());
        BOOST_CHECK( status == response.getCalibrationStatus());
        BOOST_CHECK( 1 == response.getSystemVersion());
        BOOST_CHECK( (sizeof(ResponseType::CALIBRATING_STATUS) + sizeof(CalibrationStatus::IN_THE_PROCESS)) == response.getDataSize());
        BOOST_CHECK( "CalibratingStatusResponse" == response.getName());
    }

    BOOST_AUTO_TEST_CASE( planeDataset )
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
        response.getFrameBytes();

        uint16_t datasetSize =  plane_1.size() + plane_2.size() + plane_3.size() + plane_4.size();

        BOOST_CHECK( FrameType::RESPONSE == response.getFrameType());
        BOOST_CHECK( ResponseType::PLANES_DATASET == response.getResponseType());
        BOOST_CHECK( dataset == response.getDataset());
        BOOST_CHECK( 1 == response.getSystemVersion());
        BOOST_CHECK( (sizeof(ResponseType::PLANES_DATASET) + datasetSize + dataset.size()* sizeof(END_STRING_IN_FRAME)) == response.getDataSize());
        BOOST_CHECK( "PlanesDatasetResponse" == response.getName());
    }

BOOST_AUTO_TEST_SUITE_END()

