#define BOOST_TEST_MODULE ResponseFactory

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../ResponseFactory.h"
#include "../DataResponse.h"
#include "../AckResponse.h"

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

BOOST_AUTO_TEST_SUITE_END()

