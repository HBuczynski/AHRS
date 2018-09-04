#define BOOST_TEST_MODULE UICommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../GUIWindowCommand.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( command )

        BOOST_AUTO_TEST_CASE( windowSet )
        {
                WindowType type = WindowType::SHUTDOWN;

                GUIWindowCommand command(type);
                command.getFrameBytes();

                BOOST_CHECK( type == command.getWindowType());
                BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
                BOOST_CHECK( GUICommandType::CHANGE_WINDOW == command.getCommandType());
                BOOST_CHECK( 1 == command.getSystemVersion());
                BOOST_CHECK( ((sizeof(type) + sizeof(GUICommandType::CHANGE_WINDOW)) == command.getDataSize()));
                BOOST_CHECK( "GUIWindowCommand" == command.getName());
        }


BOOST_AUTO_TEST_SUITE_END()