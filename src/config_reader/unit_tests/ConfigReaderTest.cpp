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

        const auto feederParameters = ConfigurationReader::getFeederParameters(filePath);

        BOOST_CHECK( feederParameters.sourcePort == 8000);
        BOOST_CHECK( feederParameters.maxUserNumber == 2);
        BOOST_CHECK( feederParameters.mainProcessQueueName == "MainProcessQueue");
        BOOST_CHECK( feederParameters.externalCommunicationQueueName == "ExternalCommunicationQueue");
        BOOST_CHECK( feederParameters.internalCommunicationQueueName == "InternalCommunicationQueue");
        BOOST_CHECK( feederParameters.messageSize == 400);
        BOOST_CHECK( feederParameters.externalMemoryName == "ExternalMemoryFeeder");
        BOOST_CHECK( feederParameters.internalMemoryName == "InternalMemoryFeeder");
        BOOST_CHECK( feederParameters.sharedMemorySize == 100);

    }

    BOOST_AUTO_TEST_CASE( ui )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/test.json");

        const auto uiParameters = ConfigurationReader::getUIParameters(filePath);

        BOOST_CHECK( uiParameters.sourcePort == 9000);
        BOOST_CHECK( uiParameters.sourceAddress == "127.0.0.1");
        BOOST_CHECK( uiParameters.destinationPort == 8000);
        BOOST_CHECK( uiParameters.destinationAddress == "127.0.0.1");
        BOOST_CHECK( uiParameters.mainProcessQueueName == "MainProcessQueue");
        BOOST_CHECK( uiParameters.mainCommunicationQueueName == "MainCommunicationQueue");
        BOOST_CHECK( uiParameters.redundantCommunicationQueueName == "RedundantCommunicationQueue");
        BOOST_CHECK( uiParameters.guiProcessQueueName == "GuiProcessQueue");
        BOOST_CHECK( uiParameters.messageSize == 400);
        BOOST_CHECK( uiParameters.dataSharedMemory == "SharedMemoryUI");
        BOOST_CHECK( uiParameters.sharedMemorySize == 100);
    }

BOOST_AUTO_TEST_SUITE_END()