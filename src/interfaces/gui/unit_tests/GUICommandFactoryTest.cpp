#define BOOST_TEST_MODULE UICommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../GUIWindowCommand.h"
#include "../GUIBITSCommand.h"
#include "../GUIPlanesSetCommand.h"
#include "../GUICommandFactory.h"

#include <iostream>

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( commandFactory )

        BOOST_AUTO_TEST_CASE( windowSet )
        {
            GUICommandFactory factory;
            PagesType type = PagesType::CONNECTING_PAGE;

            GUIWindowCommand command(type);

            auto commandFromVec = static_pointer_cast<GUIWindowCommand, GUICommand>(factory.createCommand(command.getFrameBytes()));

            BOOST_CHECK( commandFromVec->getWindowType() == command.getWindowType());
            BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
            BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
            BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
            BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
            BOOST_CHECK( commandFromVec->getName() == command.getName());
        }

    BOOST_AUTO_TEST_CASE( informationSet )
    {
        GUICommandFactory factory;
        BitsInformation info;
        info.mode = 23;
        info.m_communication = 43;

        GUIBITSCommand command(info);
        auto commandFromVec = static_pointer_cast<GUIBITSCommand, GUICommand>(factory.createCommand(command.getFrameBytes()));
        const auto temp = commandFromVec->getBitsInfo();

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getFrameType() == command.getFrameType());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == command.getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
        BOOST_CHECK( info.mode == temp.mode );
        BOOST_CHECK( info.m_communication == temp.m_communication );
    }

    BOOST_AUTO_TEST_CASE( planesSet )
    {
        GUICommandFactory factory;
        string planes = "Boeing, Trolo";

        GUIPlanesSetCommand command(planes);
        auto commandFromVec = static_pointer_cast<GUIPlanesSetCommand, GUICommand>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getFrameType() == command.getFrameType());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( commandFromVec->getSystemVersion() == command.getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
        BOOST_CHECK(commandFromVec->getDataset() == command.getDataset());
    }


BOOST_AUTO_TEST_SUITE_END()
