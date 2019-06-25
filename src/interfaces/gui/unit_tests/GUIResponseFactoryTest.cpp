#define BOOST_TEST_MODULE UICommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../GUIPlaneResponse.h"
#include "../GUIResponseFactory.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( responseFactory )

        BOOST_AUTO_TEST_CASE( windowSet )
        {
            GUIResponseFactory factory;
            config::UICommunicationMode mode = config::UICommunicationMode::MASTER;

            std::string plane = "Lololo";
            GUIPlaneResponse command(mode, plane);

            auto commandFromVec = static_pointer_cast<GUIPlaneResponse, GUIResponse>(factory.createCommand(command.getFrameBytes()));

            BOOST_CHECK( commandFromVec->getPlane() == command.getPlane());
            BOOST_CHECK( commandFromVec->getMode() == command.getMode());
            BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
            BOOST_CHECK( commandFromVec->getResponseType() == command.getResponseType());
            BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
            BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
            BOOST_CHECK( commandFromVec->getName() == command.getName());
        }


BOOST_AUTO_TEST_SUITE_END()
