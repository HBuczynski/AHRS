#define BOOST_TEST_MODULE HMInterfaceFactory

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../HMNotificationFactory.h"
#include "../HMRegisterMainNotification.h"

#include <string>

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( test )

    BOOST_AUTO_TEST_CASE( mainBuilder )
    {
        HMNotificationFactory factory;

        HMNodes node = HMNodes::GUI;
        string name = "temp";
        uint32_t size = 32;

        HMRegisterMainNotification notification(node, name, size);
        auto commandFromVec = static_pointer_cast<HMRegisterMainNotification, HMNotification>(factory.createNotification(notification.getFrameBytes()));

        BOOST_CHECK( commandFromVec->getFrameBytes() == notification.getFrameBytes());
        BOOST_CHECK( commandFromVec->getFrameType() == notification.getFrameType());
        BOOST_CHECK( commandFromVec->getNotificationType() == notification.getNotificationType());
        BOOST_CHECK( commandFromVec->getHMNode() == notification.getHMNode());
        BOOST_CHECK( commandFromVec->getQueueName() == notification.getQueueName());
        BOOST_CHECK( commandFromVec->getSize() == notification.getSize());
        BOOST_CHECK( commandFromVec->getSystemVersion() == notification.getSystemVersion());
    }

BOOST_AUTO_TEST_SUITE_END()

