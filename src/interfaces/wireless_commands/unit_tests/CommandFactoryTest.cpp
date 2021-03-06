#define BOOST_TEST_MODULE FactoryTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CommandFactory.h"
#include "../CallibrateMagnetometerCommand.h"
#include "../CollectDataCommand.h"
#include "../EndConnectionCommand.h"
#include "../InitConnectionCommand.h"
#include "../SetPlaneCommand.h"
#include "../RemovePlaneDataCommand.h"
#include "../PerformBITsCommand.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( factory )

    BOOST_AUTO_TEST_CASE( calibrateMagnetometerBuilder )
    {
        CommandFactory factory;
        Action status = Action::APPROVE;

        CallibrateMagnetometerCommand command(status);

        auto commandFromVec = static_pointer_cast<CallibrateMagnetometerCommand, Command>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
        BOOST_CHECK( commandFromVec->getMagAction() == command.getMagAction());
    }

    BOOST_AUTO_TEST_CASE( removePlaneBuilder )
    {
        CommandFactory factory;
        string planeName = "temp";

        RemovePlaneDataCommand command(planeName);

        auto commandFromVec = static_pointer_cast<RemovePlaneDataCommand, Command>(factory.createCommand(command.getFrameBytes()));
        BOOST_CHECK(commandFromVec->getPlaneName() == command.getPlaneName());
        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

    BOOST_AUTO_TEST_CASE( collectDataBuilder )
    {
        CommandFactory factory;
        CollectDataCommand command;

        auto commandFromVec = static_pointer_cast<CollectDataCommand, Command>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

    BOOST_AUTO_TEST_CASE( endConnectionBuilder )
    {
        CommandFactory factory;
        EndConnectionCommand command;

        auto commandFromVec = static_pointer_cast<EndConnectionCommand, Command>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

    BOOST_AUTO_TEST_CASE( initConnectionBuilder )
    {
        CommandFactory factory;
        uint16_t port = 5678;
        string address("127.0.0.1");
        InitConnectionCommand command(port, address);

        auto commandFromVec = static_pointer_cast<InitConnectionCommand, Command>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getPort() == command.getPort());
        BOOST_CHECK( commandFromVec->getAddress() == command.getAddress());
        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

    BOOST_AUTO_TEST_CASE( setPlaneMagnetometerBuilder )
    {
        CommandFactory factory;
        string planeName = "temp";
        SetPlaneCommand command(planeName);

        auto commandFromVec = static_pointer_cast<SetPlaneCommand, Command>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getPlaneName() == command.getPlaneName());
        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

    BOOST_AUTO_TEST_CASE( performBITCommandBuilder )
    {
        CommandFactory factory;

        PerformBITsCommand command;

        auto commandFromVec = static_pointer_cast<PerformBITsCommand, Command>(factory.createCommand(command.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

BOOST_AUTO_TEST_SUITE_END()
