#define BOOST_TEST_MODULE FeederCommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CalibrationStatusNotification.h"
#include "interfaces/communication_process_feeder/CalibrateMgnDemandCommand.h"

#include <string>

using namespace std;
using namespace communication;


BOOST_AUTO_TEST_SUITE( feeder )

    BOOST_AUTO_TEST_CASE( calibrationStatusNotification )
    {
            CalibrationStatus status = CalibrationStatus::IN_THE_PROCESS;
            CalibrationStatusNotification notification(status);
            notification.getFrameBytes();

            BOOST_CHECK( FrameType::NOTIFICATION == notification.getFrameType());
            BOOST_CHECK( FeederNotificationType::CALIBRATION_STATUS_NOTIFY == notification.getNotificationType());
            BOOST_CHECK( status == notification.getCalibrationStatus());
            BOOST_CHECK( 1 == notification.getSystemVersion());
            BOOST_CHECK( (sizeof(FeederNotificationType::CALIBRATION_STATUS_NOTIFY)+ sizeof(status)) == notification.getDataSize());
            BOOST_CHECK( "CalibrationStatusNotification" == notification.getName());
    }

    BOOST_AUTO_TEST_CASE( calibrateMagnetometerCommand )
    {
            string planeName = "temp";

            CalibrateMgnDemandCommand command(planeName);
            command.getFrameBytes();

            BOOST_CHECK( planeName == command.getPlaneName());
            BOOST_CHECK( FrameType::COMMAND == command.getFrameType());
            BOOST_CHECK( FeederCommandType::CALIBRATE_MAGNETOMETER_DEMAND == command.getCommandType());
            BOOST_CHECK( 1 == command.getSystemVersion());
            BOOST_CHECK( (planeName.size()+ sizeof(END_STRING_IN_FRAME) + sizeof(FeederCommandType::CALIBRATE_MAGNETOMETER_DEMAND)) == command.getDataSize());
            BOOST_CHECK( "CalibrateMgnDemandCommand" == command.getName());
    }

BOOST_AUTO_TEST_SUITE_END()


