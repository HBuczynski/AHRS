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

BOOST_AUTO_TEST_SUITE_END()

