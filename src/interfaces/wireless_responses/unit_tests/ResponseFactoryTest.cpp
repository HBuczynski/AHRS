#define BOOST_TEST_MODULE ResponseFactory

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../ResponseFactory.h"
#include "../DataResponse.h"
#include "../AckResponse.h"
#include "../CalibratingStatusResponse.h"
#include "../PlanesDatasetResponse.h"

#include <config_reader/AircraftParameters.h>
#include <string>

using namespace std;
using namespace config;
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
        vector<AircraftParameters> dataset;

        AircraftParameters plane_1;
        const char *temp = "Boeing";
        strcpy(plane_1.name, temp);
        dataset.push_back(plane_1);

        AircraftParameters plane_2;
        const char *temp_2 = "bombardier4";
        strcpy(plane_1.name, temp_2);
        dataset.push_back(plane_2);

        AircraftParameters plane_3;
        const char *temp_3 = "boeing_kk5";
        strcpy(plane_1.name, temp_3);
        dataset.push_back(plane_3);

        AircraftParameters plane_4;
        const char *temp_4 = "airbus_11";
        strcpy(plane_1.name, temp_4);
        dataset.push_back(plane_4);

        PlanesDatasetResponse response(dataset);

        ResponseFactory factory;

        auto responseFromVec = static_pointer_cast<PlanesDatasetResponse, Response>(factory.createCommand(response.getFrameBytes()));

        bool isSuccess = true;
        const auto dataset2 = response.getDataset();

        for(uint8_t i = 0; i < dataset.size(); ++i)
        {
            isSuccess = isSuccess & compareNames(dataset[i].name, dataset2[i].name, 32);
        }

        BOOST_CHECK( responseFromVec->getFrameType() == response.getFrameType());
        BOOST_CHECK( isSuccess == true);
        BOOST_CHECK( responseFromVec->getResponseType() == response.getResponseType());
        BOOST_CHECK( responseFromVec->getFrameBytes() == response.getFrameBytes());
        BOOST_CHECK( responseFromVec->getSystemVersion() == response.getSystemVersion());
        BOOST_CHECK( responseFromVec->getDataSize() == response.getDataSize());
        BOOST_CHECK( responseFromVec->getName() == response.getName());
    }

BOOST_AUTO_TEST_SUITE_END()

