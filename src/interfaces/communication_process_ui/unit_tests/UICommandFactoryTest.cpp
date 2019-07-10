#define BOOST_TEST_MODULE UICommandFactoryTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../UICommandFactory.h"
#include "../UIChangeModeCommand.h"
#include "../SendingDataCommand.h"
#include "../ShutdownCommand.h"
#include "../ReconnectCommand.h"

using namespace std;
using namespace communication;


BOOST_AUTO_TEST_SUITE( factory )

    BOOST_AUTO_TEST_CASE( uiChangeModeCommand )
    {
            UICommandFactory factory;
            config::UICommunicationMode mode = config::UICommunicationMode::MASTER;

            UIChangeModeCommand command(mode);

            auto commandFromVec = static_pointer_cast<UIChangeModeCommand, UICommand>(factory.createCommand(command.getFrameBytes()));

            BOOST_CHECK( commandFromVec->getMode() == command.getMode());
            BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
            BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
            BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
            BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
            BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

    BOOST_AUTO_TEST_CASE( sendingDataCommand )
    {
        UICommandFactory factory;
        vector<uint8_t> temp(9,9);
        SendingDataCommand command(temp);
        command.getFrameBytes();

        auto commandFromVec = static_pointer_cast<SendingDataCommand, UICommand>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getDataFrame() == command.getDataFrame());
        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

    BOOST_AUTO_TEST_CASE( shutdownCommand )
    {
        UICommandFactory factory;
        ShutdownCommand command;
        command.getFrameBytes();

        auto commandFromVec = static_pointer_cast<ShutdownCommand, UICommand>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());;
    }

    BOOST_AUTO_TEST_CASE( reconnectCommand )
    {
        UICommandFactory factory;
        ReconnectCommand command;
        command.getFrameBytes();

        auto commandFromVec = static_pointer_cast<ReconnectCommand, UICommand>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

BOOST_AUTO_TEST_SUITE_END()
