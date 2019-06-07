#define BOOST_TEST_MODULE HMInterfaceTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../HMRegisterMainNotification.h"

#include <string>
#include <stdio.h>

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( hmInterface )

    BOOST_AUTO_TEST_CASE( hmMainRegister )
    {
        HMNodes node = HMNodes::GUI;
        string name = "temp";
        uint32_t size = 32;

        HMRegisterMainNotification notification(node, name, size);
        notification.getFrameBytes();

        BOOST_CHECK( FrameType::NOTIFICATION == notification.getFrameType());
        BOOST_CHECK( HMNotificationType::MAIN_REGISTER == notification.getNotificationType());
        BOOST_CHECK( HMNodes::GUI == notification.getHMNode());
        BOOST_CHECK( name == notification.getQueueName());
        BOOST_CHECK( size == notification.getQueueSize());
        BOOST_CHECK( 1 == notification.getSystemVersion());
        BOOST_CHECK( (sizeof(HMNotificationType::MAIN_REGISTER) + sizeof(HMNodes::GUI) + sizeof(size) + name.size() + 1) == notification.getDataSize());
        BOOST_CHECK( "HMRegisterMainNotification" == notification.getName());
    }


BOOST_AUTO_TEST_SUITE_END()

