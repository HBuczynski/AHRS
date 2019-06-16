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

        BOOST_CHECK(feederInternalWireless.destinationAddress == "127.0.0.1" );
        BOOST_CHECK(feederInternalWireless.sourceAddress == "127.0.0.1" );
        BOOST_CHECK(feederInternalWireless.destinationPort == 5000);
        BOOST_CHECK(feederInternalWireless.sourcePort == 4000);
    }

    BOOST_AUTO_TEST_CASE( uiButtons )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/ui_buttons.json");
        const auto uiButtons = ConfigurationReader::getUISwitches(filePath);

        const auto firstButton = uiButtons[0];
        const auto secondButton = uiButtons[1];
        const auto thirdButton = uiButtons[2];
        const auto fourthButton = uiButtons[3];

        BOOST_CHECK(firstButton.pinNumber == 14 );
        BOOST_CHECK(firstButton.pinMode == hardware::GPIOMode::IN);
        BOOST_CHECK(firstButton.pushPullMode == hardware::GPIOPullMode::UP);

        BOOST_CHECK(secondButton.pinNumber == 15 );
        BOOST_CHECK(secondButton.pinMode == hardware::GPIOMode::IN);
        BOOST_CHECK(secondButton.pushPullMode == hardware::GPIOPullMode::UP);

        BOOST_CHECK(thirdButton.pinNumber == 18 );
        BOOST_CHECK(thirdButton.pinMode == hardware::GPIOMode::IN);
        BOOST_CHECK(thirdButton.pushPullMode == hardware::GPIOPullMode::UP);

        BOOST_CHECK(fourthButton.pinNumber == 23 );
        BOOST_CHECK(fourthButton.pinMode == hardware::GPIOMode::IN);
        BOOST_CHECK(fourthButton.pushPullMode == hardware::GPIOPullMode::UP);
    }

    BOOST_AUTO_TEST_CASE( uiExecutableFiles )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/ui_parameters.json");
        const auto executableFiles = ConfigurationReader::getUIExecutableFiles(filePath);

        BOOST_CHECK(executableFiles.guiProcess == "gui");
        BOOST_CHECK(executableFiles.externalCommunicationProcess == "external_ui_communication");

    }

    BOOST_AUTO_TEST_CASE( uiWirelessCommunication )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/ui_parameters.json");
        const auto wirelessCommunication = ConfigurationReader::getUIWirelessCommunication(filePath);

        BOOST_CHECK(wirelessCommunication.firstSourcePort == 9000);
        BOOST_CHECK(wirelessCommunication.firstSourceAddress == "127.0.0.1");
        BOOST_CHECK(wirelessCommunication.secondSourcePort == 6000);
        BOOST_CHECK(wirelessCommunication.secondSourceAddress == "127.0.0.1");

        BOOST_CHECK(wirelessCommunication.firstDestinationPort == 8000);
        BOOST_CHECK(wirelessCommunication.firstDestinationAddress == "127.0.0.1");
        BOOST_CHECK(wirelessCommunication.secondDestinationPort == 8000);
        BOOST_CHECK(wirelessCommunication.secondDestinationAddress == "127.0.0.1");
    }

    BOOST_AUTO_TEST_CASE( uiMessageQueues )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/ui_parameters.json");
        const auto uiMessageQueues = ConfigurationReader::getUIMessageQueues(filePath);

        BOOST_CHECK(uiMessageQueues.guiProcessQueueName == "GuiProcessQueue");
        BOOST_CHECK(uiMessageQueues.mainProcessQueueName == "MainProcessQueue");
        BOOST_CHECK(uiMessageQueues.secondCommunicationQueueName == "SecondCommunicationQueueName");
        BOOST_CHECK(uiMessageQueues.firstCommunicationQueueName == "FirstCommunicationQueueName");
        BOOST_CHECK(uiMessageQueues.messageQueueNumber == 20);
        BOOST_CHECK(uiMessageQueues.messageSize == 400);
    }

    BOOST_AUTO_TEST_CASE( uiSharedMemory )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/ui_parameters.json");
        const auto uiSharedMemory = ConfigurationReader::getUISharedMemory(filePath);

        BOOST_CHECK(uiSharedMemory.sharedMemorySize == 100 );
        BOOST_CHECK(uiSharedMemory.sharedMemoryName == "SharedMemoryUI");
    }

    BOOST_AUTO_TEST_CASE( uiCommunicationSystemParameters )
    {
        const string filePath("../../src/config_reader/unit_tests/test_files/ui_communication_processes.json");
        const auto uiCommunicationProcesses = ConfigurationReader::getUICommunicationProcessSystemParameters(filePath);

        BOOST_CHECK(uiCommunicationProcesses.firstProcess.mode == UICommunicationMode::MASTER);
        BOOST_CHECK(uiCommunicationProcesses.secondProcess.mode == UICommunicationMode::REDUNDANT);
        BOOST_CHECK(uiCommunicationProcesses.firstProcess.processNumber == 1);
        BOOST_CHECK(uiCommunicationProcesses.secondProcess.processNumber == 2);
    }

BOOST_AUTO_TEST_SUITE_END()