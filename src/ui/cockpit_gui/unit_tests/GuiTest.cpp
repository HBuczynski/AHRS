#define BOOST_TEST_MODULE GUI

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <cockpit_gui/MainWindow.h>

BOOST_AUTO_TEST_SUITE( test_multiply )

        BOOST_AUTO_TEST_CASE( test_int )
        {

                BOOST_CHECK( 21 == 21);
        }

BOOST_AUTO_TEST_SUITE_END()
