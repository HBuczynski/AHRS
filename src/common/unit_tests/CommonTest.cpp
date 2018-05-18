#define BOOST_TEST_MODULE CommonTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Common.h"

using namespace common;
using namespace std;

BOOST_AUTO_TEST_SUITE( common )

        BOOST_AUTO_TEST_CASE( parser_checking )
        {
                //CommunicationParameters parameters = Common::getCommunicationParameters();

                BOOST_CHECK( 1 == 1);
        }

BOOST_AUTO_TEST_SUITE_END()