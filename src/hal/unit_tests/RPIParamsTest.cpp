#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../include/RPIParams.h"

using namespace std;

BOOST_AUTO_TEST_SUITE( params )

    BOOST_AUTO_TEST_CASE( temp )
    {
        RPIParams param;
        cout << param.getTemp() << endl;
    }

BOOST_AUTO_TEST_SUITE_END()
