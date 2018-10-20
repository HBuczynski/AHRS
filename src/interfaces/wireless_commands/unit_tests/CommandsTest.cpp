#define BOOST_TEST_MODULE CommandTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CallibrateMagnetometerCommand.h"
#include "../CollectDataCommand.h"
#include "../EndConnectionCommand.h"
#include "../InitConnectionCommand.h"
#include "../SetPlaneMagnetometerCommand.h"
#include "../RemovePlaneDataCommand.h"
#include "../PerformBITsCommand.h"

#include <string>

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( commands )

    BOOST_AUTO_TEST_CASE( calibrateMagnetometerCommand )
    {
        string planeName = "temp";
        PlaneStatus status = PlaneStatus::NEW;

        CallibrateMagnetometerCommand command(planeName, status);
        command.getFrameBytes();

        BOOST_CHECK( planeName == command.getPlaneName());
        BOOST_CHECK( status == command.getPlaneStatus());
        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( CommandType::CALIBRATE_MAGNETOMETER == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (planeName.size()+ sizeof(END_STRING_IN_FRAME) + sizeof(CommandType::CALIBRATE_MAGNETOMETER) +
                sizeof(status)) == command.getDataSize());
        BOOST_CHECK( "CallibrateMagnetometerCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( removePlaneCommand )
    {
        string planeName = "temp";

        RemovePlaneDataCommand command(planeName);
        command.getFrameBytes();

        BOOST_CHECK( planeName == command.getPlaneName());
        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( CommandType::REMOVE_PLANE_DATA == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (planeName.size()+ sizeof(END_STRING_IN_FRAME) + sizeof(CommandType::REMOVE_PLANE_DATA)) == command.getDataSize());
        BOOST_CHECK( "RemovePlaneDataCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( collectDataCommand )
    {
        CollectDataCommand command;
        command.getFrameBytes();

        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( CommandType::COLLECT_DATA == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (sizeof(CommandType::COLLECT_DATA)) == command.getDataSize());
        BOOST_CHECK( "CollectDataCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( endConnectionCommand )
    {
        EndConnectionCommand command;
        command.getFrameBytes();

        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( CommandType::END_CONNECTION == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (sizeof(CommandType::END_CONNECTION)) == command.getDataSize());
        BOOST_CHECK( "EndConnectionCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( initConnectionCommand )
    {
        string address = "127.0.0.1";
        uint16_t port = 8765;

        InitConnectionCommand command(port, address);
        command.getFrameBytes();

        BOOST_CHECK( address == command.getAddress());
        BOOST_CHECK( port == command.getPort());
        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( CommandType::INIT_CONNECTION == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (address.size()+ sizeof(port)+sizeof(END_STRING_IN_FRAME) + sizeof(CommandType::CALIBRATE_MAGNETOMETER)) == command.getDataSize());
        BOOST_CHECK( "InitConnectionCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( setPlaneMagnetometerCommand )
    {
        string planeName = "temp";

        SetPlaneMagnetometerCommand command(planeName);
        command.getFrameBytes();

        BOOST_CHECK( planeName == command.getPlaneName());
        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( CommandType::SET_PLANE_MAGNETOMETER_DATA == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (planeName.size()+ sizeof(END_STRING_IN_FRAME) + sizeof(CommandType::SET_PLANE_MAGNETOMETER_DATA)) == command.getDataSize());
        BOOST_CHECK( "SetPlaneMagnetometerCommand" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( performBITCommand )
    {
        PerformBITsCommand command;
        command.getFrameBytes();

        BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
        BOOST_CHECK( CommandType::PERFORM_BIT == command.getCommandType());
        BOOST_CHECK( 1 == command.getSystemVersion());
        BOOST_CHECK( (sizeof(CommandType::PERFORM_BIT)) == command.getDataSize());
        BOOST_CHECK( "PerformBITsCommand" == command.getName());
    }



BOOST_AUTO_TEST_SUITE_END()
