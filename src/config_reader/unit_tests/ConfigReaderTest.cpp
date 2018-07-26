#define BOOST_TEST_MODULE ConfigReaderTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "config_reader/ConfigurationReader.h"

using namespace config;
using namespace utility;
using namespace std;

BOOST_AUTO_TEST_SUITE( parser )

    BOOST_AUTO_TEST_CASE( checking )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/test.json");

        system("pwd");
        const auto configurationParameters = ConfigurationReader::getCommunicationParameters(filePath);

        BOOST_CHECK( configurationParameters.destinationAddressTCP == "10.10.10.20");
        BOOST_CHECK( configurationParameters.destinationPortTCP == 8000);
        BOOST_CHECK( configurationParameters.sourceAddressUDP == "127.0.0.1");
        BOOST_CHECK( configurationParameters.sourcePortUDP == 9000);
    }

BOOST_AUTO_TEST_SUITE_END()