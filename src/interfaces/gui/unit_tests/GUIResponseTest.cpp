#define BOOST_TEST_MODULE UICommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../GUIPlaneResponse.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( response )

        BOOST_AUTO_TEST_CASE( windowSet )
        {
            std::string plane = "Lololo";
            config::UICommunicationMode mode = config::UICommunicationMode::MASTER;

            GUIPlaneResponse response(mode, plane);
            response.getFrameBytes();

            BOOST_CHECK( plane == response.getPlane());
            BOOST_CHECK( mode == response.getMode());
            BOOST_CHECK( FrameType::RESPONSE == response.getFrameType());
            BOOST_CHECK( GUIResponseType::SET_PLANE == response.getResponseType());
            BOOST_CHECK( 1 == response.getSystemVersion());
            BOOST_CHECK( (plane.size() + sizeof(END_STRING_IN_FRAME) + sizeof(mode) + sizeof(GUIResponseType::SET_PLANE )) == response.getDataSize());
            BOOST_CHECK( "GUIPlaneResponse" == response.getName());
        }


BOOST_AUTO_TEST_SUITE_END()
