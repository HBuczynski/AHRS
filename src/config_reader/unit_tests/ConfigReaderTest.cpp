#define BOOST_TEST_MODULE ConfigReaderTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "config_reader/JSONParser.h"

using namespace config;
using namespace utility;
using namespace std;

BOOST_AUTO_TEST_SUITE( parser )

    BOOST_AUTO_TEST_CASE( parser_checking )
    {
        Logger &logger = Logger::getInstance();

        InitLogStructure struc;
        struc.debugLog = true;
        struc.errroLog = true;
        struc.informationLog = true;
        struc.warningLog = true;

        struc.writeLogsInSeparetFiles = true;
        struc.writeOnConsole = true;

        logger.initLogger(struc);

        JSONParser parser("../../src/config_reader/unit_tests/test.json");

        string stringTest;
        {
            vector<string> vec;
            vec.push_back("Note");

            parser.getString(vec, stringTest);
        }
        BOOST_CHECK( stringTest == string("This is a cofiguration file"));

        uint8_t uint8Test;
        {
            vector<string> vec;
            vec.push_back("Config");
            vec.push_back("test-format");
            vec.push_back("test_number");

            parser.getUINT8t(vec, uint8Test);
        }
        BOOST_CHECK( uint8Test == 23);

        uint16_t uint16Test;
        {
            vector<string> vec;
            vec.push_back("Config");
            vec.push_back("buffer-length");

            parser.getUINT16t(vec, uint16Test);
        }
        BOOST_CHECK( uint16Test == 5000);

        uint32_t uint32Test;
        {
            vector<string> vec;
            vec.push_back("Config");
            vec.push_back("trolo");

            parser.getUINT32t(vec, uint32Test);
        }
        BOOST_CHECK( uint32Test == 5000000);

        uint64_t uint64Test;
        {
            vector<string> vec;
            vec.push_back("Config");
            vec.push_back("long_trolo");

            parser.getUINT64t(vec, uint64Test);
        }
        BOOST_CHECK( uint64Test == 98765000);
    }

BOOST_AUTO_TEST_SUITE_END()