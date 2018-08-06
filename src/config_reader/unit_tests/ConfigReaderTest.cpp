#define BOOST_TEST_MODULE ConfigReaderTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "config_reader/ConfigurationReader.h"

using namespace config;
using namespace utility;
using namespace std;

BOOST_AUTO_TEST_SUITE( parser )

    BOOST_AUTO_TEST_CASE( feeder )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/test.json");

        const auto lol = ConfigurationReader::getUIWirelessCommunication(filePath);


    }

    BOOST_AUTO_TEST_CASE( ui )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/test.json");


    }

BOOST_AUTO_TEST_SUITE_END()