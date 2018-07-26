#define BOOST_TEST_MODULE Test

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Logger.h"
#include <time_manager/TimeManager.h>

BOOST_AUTO_TEST_SUITE( logger )

    BOOST_AUTO_TEST_CASE( checking )
    {

        BOOST_CHECK( 9000 == 9000);
    }

BOOST_AUTO_TEST_SUITE_END()