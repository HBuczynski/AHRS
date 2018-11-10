#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../Checksum.h"


using namespace std;
using namespace utility;


BOOST_AUTO_TEST_SUITE( checksum_test )

    BOOST_AUTO_TEST_CASE( parityBit )
    {
        vector<uint8_t> frame = {254, 255, 7, 1};

        const auto parity = Checksum::parityBit(frame);

        BOOST_CHECK( parity == 1);

    }

    BOOST_AUTO_TEST_CASE( crc )
    {
        vector<uint8_t> frame = {1};

        const auto crc = Checksum::crc32(frame);

        BOOST_CHECK( crc == 2768625435);

    }

BOOST_AUTO_TEST_SUITE_END()
