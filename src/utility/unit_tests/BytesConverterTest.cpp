#define BOOST_TEST_MODULE SqrTests
#include <boost/test/unit_test.hpp>

#include "../BytesConverter.h"

BOOST_AUTO_TEST_CASE(FailTest)
{
    BOOST_CHECK_EQUAL(5, 5);
}

BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_CHECK_EQUAL(4, 4);
}
