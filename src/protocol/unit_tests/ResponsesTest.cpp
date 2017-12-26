#define BOOST_TEST_MODULE ResponsesTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../DataResponse.h"
#include "../AckResponse.h"

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

BOOST_AUTO_TEST_SUITE_END()

