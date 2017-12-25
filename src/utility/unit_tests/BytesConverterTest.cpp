#define BOOST_TEST_MODULE BytesConverterTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../BytesConverter.h"

BOOST_AUTO_TEST_SUITE(Conversions)

    BOOST_AUTO_TEST_CASE(ConvertUIN16toVectorAndReverse)
    {
        uint16_t number = 64654;
        std::vector<uint8_t> vec;

        utility::BytesConverter::appendUINT16toVectorOfUINT8(number, vec);

        uint16_t numberAferReverse;
        numberAferReverse = utility::BytesConverter::fromVectorOfUINT8toUINT16(vec, 0);

        BOOST_CHECK_EQUAL(number, numberAferReverse);
    }

    BOOST_AUTO_TEST_CASE(ConvertUIN32toVectorAndReverse)
    {
        uint32_t number = 3999888777;
        std::vector<uint8_t> vec;

        utility::BytesConverter::appendUINT32toVectorOfUINT8(number, vec);

        uint32_t numberAferReverse;
        numberAferReverse = utility::BytesConverter::fromVectorOfUINT8toUINT32(vec, 0);

        BOOST_CHECK_EQUAL(number, numberAferReverse);
    }

    BOOST_AUTO_TEST_CASE(ConvertUIN64toVectorAndReverse)
    {
        uint64_t number = 3999888777000666555;
        std::vector<uint8_t> vec;

        utility::BytesConverter::appendUINT64toVectorOfUINT8(number, vec);

        uint64_t numberAferReverse;
        numberAferReverse = utility::BytesConverter::fromVectorOfUINT8toUINT64(vec, 0);

        BOOST_CHECK_EQUAL(number, numberAferReverse);
    }


BOOST_AUTO_TEST_SUITE_END()

