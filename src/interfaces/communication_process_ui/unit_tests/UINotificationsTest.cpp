#define BOOST_TEST_MODULE UINotificationTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CommunicationStatusNotification.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( notification )

        BOOST_AUTO_TEST_CASE( communicationStatusNotification )
        {
                BOOST_CHECK( 1 == 1);
        }

BOOST_AUTO_TEST_SUITE_END()
