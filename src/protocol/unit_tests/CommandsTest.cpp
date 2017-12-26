#define BOOST_TEST_MODULE CommandTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../CallibrateMagnetometerCommand.h"
#include "../CollectDataCommand.h"
#include "../EndConnectionCommand.h"
#include "../InitConnectionCommand.h"
#include "../SetPlaneMagnetometerCommand.h"

BOOST_AUTO_TEST_SUITE( commands )

    BOOST_AUTO_TEST_CASE( test_int )
    {
        BOOST_CHECK( 21 == 21);
    }

BOOST_AUTO_TEST_SUITE_END()
