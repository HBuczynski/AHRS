#define BOOST_TEST_MODULE ServerTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CockpitDb.h"

using namespace database;

BOOST_AUTO_TEST_SUITE( cockpit )

        BOOST_AUTO_TEST_CASE( test_int )
        {
            CockpitDb cockpitDb;
        }

BOOST_AUTO_TEST_SUITE_END()

