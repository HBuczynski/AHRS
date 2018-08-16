#define BOOST_TEST_MODULE ConfigReaderTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "config_reader/ConfigurationReader.h"

using namespace config;
using namespace utility;
using namespace std;

BOOST_AUTO_TEST_SUITE( parser )

    BOOST_AUTO_TEST_CASE( feederType )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/feeder_system.json");

        const auto feederType = ConfigurationReader::getFeederType(filePath);

        BOOST_CHECK( feederType.mode == FeederMode::MASTER);
        BOOST_CHECK( feederType.processNumber == 1);
    }

    BOOST_AUTO_TEST_CASE( feederMessageQueues )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/feeder_parameters.json");

        const auto feederMessageQueues = ConfigurationReader::getFeederMessageQueues(filePath);

        BOOST_CHECK( feederMessageQueues.mainProcessQueueName == "MainProcessQueue");
        BOOST_CHECK( feederMessageQueues.internalCommunicationQueueName == "InternalCommunicationQueue");
        BOOST_CHECK( feederMessageQueues.externalCommunicationQueueName == "ExternalCommunicationQueue");
        BOOST_CHECK( feederMessageQueues.messageSize == 400);
        BOOST_CHECK( feederMessageQueues.messageQueueNumber == 30);
    }

    BOOST_AUTO_TEST_CASE( feederSharedMemory )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/feeder_parameters.json");

        const auto feederSharedMemory = ConfigurationReader::getFeederSharedMemory(filePath);

        BOOST_CHECK( feederSharedMemory.externalMemoryName == "ExternalMemoryFeeder");
        BOOST_CHECK( feederSharedMemory.internalMemoryName == "InternalMemoryFeeder");
        BOOST_CHECK( feederSharedMemory.sharedMemorySize == 100);
    }

    BOOST_AUTO_TEST_CASE( feederExecutableFiles )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/feeder_parameters.json");

        const auto feederExecutableFiles = ConfigurationReader::getFeederExecutableFiles(filePath);

        BOOST_CHECK(feederExecutableFiles.internalCommunication == "lololo");
        BOOST_CHECK(feederExecutableFiles.externalCommunication == "lololo");

    }

    BOOST_AUTO_TEST_CASE( feederExternalWireless )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/feeder_parameters.json");

        const auto feederExternalWireless = ConfigurationReader::getFeederExternalWireless(filePath);

        BOOST_CHECK(feederExternalWireless.maxUserNumber == 2);
        BOOST_CHECK(feederExternalWireless.secondPort == 7000);
        BOOST_CHECK(feederExternalWireless.firstPort == 8000);
    }

    BOOST_AUTO_TEST_CASE( feederInternalWireless )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/feeder_parameters.json");
        const auto feederInternalWireless = ConfigurationReader::getFeederInternalWireless(filePath);

        BOOST_CHECK(feederInternalWireless.secondAddress == "127.0.0.1" );
        BOOST_CHECK(feederInternalWireless.firstAddress == "127.0.0.1" );
        BOOST_CHECK(feederInternalWireless.secondPort == 5000);
        BOOST_CHECK(feederInternalWireless.firstPort == 4000);
    }


BOOST_AUTO_TEST_SUITE_END()