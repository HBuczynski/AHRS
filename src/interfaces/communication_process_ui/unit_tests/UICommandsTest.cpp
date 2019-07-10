#define BOOST_TEST_MODULE UICommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../UIChangeModeCommand.h"
#include "../SendingDataCommand.h"
#include "../ShutdownCommand.h"
#include "../ReconnectCommand.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( command )

    BOOST_AUTO_TEST_CASE( uiChangeModeCommand )
    {
            config::UICommunicationMode mode = config::UICommunicationMode::MASTER;

            UIChangeModeCommand command(mode);
            command.getFrameBytes();

            BOOST_CHECK( mode == command.getMode());
            BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
            BOOST_CHECK( UICommandType::CHANGE_STATE == command.getCommandType());
            BOOST_CHECK( 1 == command.getSystemVersion());
            BOOST_CHECK( ((sizeof(mode) + sizeof(UICommandType::CHANGE_STATE)) == command.getDataSize()));
            BOOST_CHECK( "UIChangeModeCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( sendingDataCommand )
    {
        vector<uint8_t> temp(9,9);
        SendingDataCommand command(temp);
        command.getFrameBytes();

        BOOST_CHECK( temp == command.getDataFrame());
        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( UICommandType::SEND_FRAME == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (sizeof(UICommandType::CHANGE_STATE) + temp.size()) == command.getDataSize());
        BOOST_CHECK( "SendingDataCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( shutdownCommand )
    {
        ShutdownCommand command;
        command.getFrameBytes();

        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( UICommandType::SHUTDOWN == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (sizeof(UICommandType::CHANGE_STATE)) == command.getDataSize());
        BOOST_CHECK( "ShutdownCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( reconnectCommand )
    {
        ReconnectCommand command;
        command.getFrameBytes();

        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( UICommandType::RECONNECT == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (sizeof(UICommandType::CHANGE_STATE)) == command.getDataSize());
        BOOST_CHECK( "ReconnectCommand" == command.getName());
    }

BOOST_AUTO_TEST_SUITE_END()
