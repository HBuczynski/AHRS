#define BOOST_TEST_MODULE UINotificationTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CommunicationStatusNotification.h"
#include "../ReceivingDataNotification.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( notification )

    BOOST_AUTO_TEST_CASE( communicationStatusNotification )
    {
            UIExternalStateCode code = UIExternalStateCode::ERROR;
            uint8_t processNumber = 1;

            CommunicationStatusNotification command(code, processNumber);
            command.getFrameBytes();

            BOOST_CHECK( code == command.getState());
            BOOST_CHECK( processNumber == command.getProcessNumber());
            BOOST_CHECK( FrameType::NOTIFICATION == command.getFrameType());
            BOOST_CHECK( UINotificationType::COMMMUNICATION_PROCESS_STATUS == command.getCommandType());
            BOOST_CHECK( 1 == command.getSystemVersion());
            BOOST_CHECK( ((sizeof(code) + sizeof(UINotificationType::COMMMUNICATION_PROCESS_STATUS)) == command.getDataSize()));
            BOOST_CHECK( "CommunicationStatusNotification" == command.getName());
    }

    BOOST_AUTO_TEST_CASE( receivingDataNotification )
    {
            const vector<uint8_t> temp(9,9);
            ReceivingDataNotification command(temp);
            command.getFrameBytes();

            BOOST_CHECK( temp == command.getData());
            BOOST_CHECK( FrameType::NOTIFICATION == command.getFrameType());
            BOOST_CHECK( UINotificationType::RECEIVING_DATA == command.getCommandType());
            BOOST_CHECK( 1 == command.getSystemVersion());
            BOOST_CHECK( (sizeof(UINotificationType::RECEIVING_DATA ) + temp.size()) == command.getDataSize());
            BOOST_CHECK( "ReceivingDataNotification" == command.getName());
    }


BOOST_AUTO_TEST_SUITE_END()
