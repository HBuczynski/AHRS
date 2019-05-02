#define BOOST_TEST_MODULE FeederFactoryTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../FeederCommandFactory.h"
#include "../FeederNotificationFactory.h"
#include "../CalibrationStatusNotification.h"
#include "interfaces/communication_process_feeder/CalibrateMgnDemandCommand.h"

#include <string>

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( factory )

    BOOST_AUTO_TEST_CASE( calibrationStatusBuilder )
    {
        FeederNotificationFactory factory;

        NotificationStatus status = NotificationStatus::IN_THE_PROCESS;

        CalibrationStatusNotification notification(status);

        auto commandFromVec = static_pointer_cast<CalibrationStatusNotification, FeederNotification>(factory.createNotification(notification.getFrameBytes()));
        BOOST_CHECK( commandFromVec->getFrameBytes() == notification.getFrameBytes());
        BOOST_CHECK( commandFromVec->getNotificationType() == notification.getNotificationType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == notification.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == notification.getName());
        BOOST_CHECK( commandFromVec->getCalibrationStatus() == notification.getCalibrationStatus());
    }

    BOOST_AUTO_TEST_CASE( calibrateMagnetometerBuilder )
    {
        FeederCommandFactory factory;
        string planeName = "temp";

        CalibrateMgnDemandCommand command(planeName);

        auto commandFromVec = static_pointer_cast<CalibrateMgnDemandCommand, FeederCommand>(factory.createCommand(command.getFrameBytes()));
        BOOST_CHECK(commandFromVec->getPlaneName() == command.getPlaneName());
        BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
        BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
        BOOST_CHECK( 1 == commandFromVec->getSystemVersion());
        BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
        BOOST_CHECK( commandFromVec->getName() == command.getName());
    }


BOOST_AUTO_TEST_SUITE_END()

