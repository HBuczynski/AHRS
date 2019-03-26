#define BOOST_TEST_MODULE ResponsesTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../DataResponse.h"
#include "../AckResponse.h"
#include "../CalibratingStatusResponse.h"
#include "../PlanesDatasetResponse.h"

#include <string>
#include <stdio.h>

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
//        vector<AircraftParameters> dataset;
//
//        AircraftParameters plane_1;
//        const char *temp = "Boeing";
//        strcpy(plane_1.name, temp);
//        dataset.push_back(plane_1);
//
//        AircraftParameters plane_2;
//        const char *temp_2 = "bombardier4";
//        strcpy(plane_1.name, temp_2);
//        dataset.push_back(plane_2);
//
//        AircraftParameters plane_3;
//        const char *temp_3 = "boeing_kk5";
//        strcpy(plane_1.name, temp_3);
//        dataset.push_back(plane_3);
//
//        AircraftParameters plane_4;
//        const char *temp_4 = "airbus_11";
//        strcpy(plane_1.name, temp_4);
//        dataset.push_back(plane_4);
//
//        PlanesDatasetResponse response(dataset);
//        response.getFrameBytes();
//
//
//        bool isSuccess = true;
//        const auto dataset2 = response.getDataset();
//
//        for(uint8_t i = 0; i < dataset.size(); ++i)
//        {
//            isSuccess = isSuccess & compareNames(dataset[i].name, dataset2[i].name, 32);
//        }
//
//        BOOST_CHECK( FrameType::RESPONSE == response.getFrameType());
//        BOOST_CHECK( ResponseType::PLANES_DATASET == response.getResponseType());
//        BOOST_CHECK( isSuccess == true);
//        BOOST_CHECK( 1 == response.getSystemVersion());
//        BOOST_CHECK( (sizeof(ResponseType::PLANES_DATASET) + dataset.size()* sizeof(AircraftParameters)) == response.getDataSize());
//        BOOST_CHECK( "PlanesDatasetResponse" == response.getName());
    }

BOOST_AUTO_TEST_SUITE_END()

