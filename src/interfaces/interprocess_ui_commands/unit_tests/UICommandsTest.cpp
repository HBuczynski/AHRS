#define BOOST_TEST_MODULE UICommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../UIChangeModeCommand.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( command )

    BOOST_AUTO_TEST_CASE( uiChangeModeCommand )
    {
            CommunicationProcessMode mode = MAIN;

            UIChangeModeCommand command(mode);
            command.getFrameBytes();

            BOOST_CHECK( mode == command.getMode());
            BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
            BOOST_CHECK( UICommandType::CHANGE_STATE == command.getCommandType());
            BOOST_CHECK( 1 == command.getSystemVersion());
            BOOST_CHECK( ((sizeof(mode) + sizeof(UICommandType::CHANGE_STATE)) == command.getDataSize()));
            BOOST_CHECK( "UIChangeModeCommand" == command.getName());
    }
BOOST_AUTO_TEST_SUITE_END()