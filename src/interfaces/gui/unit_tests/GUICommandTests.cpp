#define BOOST_TEST_MODULE UICommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../GUIWindowCommand.h"
#include "../GUIInformationWindowCommand.h"

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

    BOOST_AUTO_TEST_CASE( informationWindow )
    {
            uint8_t master =1;
            uint8_t redundant = 1;
            uint8_t bitsMaster = 1;
            uint8_t bitsRedundant = 1;

            GUIInformationWindowCommand command(master, redundant, bitsMaster, bitsRedundant);
            command.getFrameBytes();
            
            BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
            BOOST_CHECK( GUICommandType::INFORMATION_WINDOW == command.getCommandType());
            BOOST_CHECK( 1 == command.getSystemVersion());
            BOOST_CHECK( ((sizeof(GUICommandType::INFORMATION_WINDOW) + sizeof(master) + sizeof(redundant) + sizeof(bitsMaster) + sizeof(bitsRedundant) ) == command.getDataSize()));
            BOOST_CHECK( "GUIInformationWindowCommand" == command.getName());
    }


BOOST_AUTO_TEST_SUITE_END()