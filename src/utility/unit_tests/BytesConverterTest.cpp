#define BOOST_TEST_MODULE BytesConverterTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <config_reader/AircraftParameters.h>

#include "../BytesConverter.h"

#include <string>
#include <iostream>

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

    BOOST_AUTO_TEST_CASE(ConvertStringToVectorAndReverse)
    {
        std::string name("Temp Data Frame");
        std::vector<uint8_t> vec;

        utility::BytesConverter::appendStringToVectorOfUINT8(name, vec);

        std::string nameAfterReverse = utility::BytesConverter::fromVectorOfUINT8toString(vec,0);

        BOOST_CHECK_EQUAL(name, nameAfterReverse);
    }

    BOOST_AUTO_TEST_CASE(ConvertStructToVectorAndReverse)
    {
        config::AircraftParameters aircraftParameters;
        const char *temp = "Boeing";

        strcpy(aircraftParameters.name, temp);

        uint16_t pos = 0;
        std::vector<uint8_t> vec = utility::BytesConverter::appendStructToVectorOfUINT8(aircraftParameters);

        config::AircraftParameters aircraftParameters2;
        utility::BytesConverter::fromVectorOfUINT8toStruct<config::AircraftParameters>(vec, pos, aircraftParameters2);

        bool isSuccess = true;

        for(uint8_t i = 0; i < 32; ++i)
        {
            isSuccess = isSuccess & (aircraftParameters.name[i] == aircraftParameters2.name[i]);
        }

        BOOST_CHECK_EQUAL(isSuccess, true);
    }


BOOST_AUTO_TEST_SUITE_END()

