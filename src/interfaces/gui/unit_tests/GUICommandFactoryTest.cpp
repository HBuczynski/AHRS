#define BOOST_TEST_MODULE UICommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../GUIWindowCommand.h"
#include "../GUICommandFactory.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( commandFactory )

        BOOST_AUTO_TEST_CASE( windowSet )
        {
            GUICommandFactory factory;
            WindowType type = WindowType::SHUTDOWN;

            GUIWindowCommand command(type);

            auto commandFromVec = static_pointer_cast<GUIWindowCommand, GUICommand>(factory.createCommand(command.getFrameBytes()));

            BOOST_CHECK( commandFromVec->getWindowType() == command.getWindowType());
            BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
            BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
            BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
            BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
            BOOST_CHECK( commandFromVec->getName() == command.getName());
        }


BOOST_AUTO_TEST_SUITE_END()