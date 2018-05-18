#define BOOST_TEST_MODULE FeederCommandsTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( feeder )

        BOOST_AUTO_TEST_CASE( test_int )
        {
                BOOST_CHECK( 21 == 21);
        }

BOOST_AUTO_TEST_SUITE_END()


