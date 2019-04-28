#define BOOST_TEST_MODULE UINotificationFactoryTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../UINotificationFactory.h"
#include "../CommunicationStatusNotification.h"
#include "../ReceivingDataNotification.h"

using namespace std;
using namespace communication;

BOOST_AUTO_TEST_SUITE( factory )

    BOOST_AUTO_TEST_CASE( communicationStatusNotification )
    {
            UINotificationFactory factory;
            UIExternalComCode code = UIExternalComCode::ERROR;
            uint8_t processNumber = 1;

            CommunicationStatusNotification command(code, processNumber);

            auto commandFromVec = static_pointer_cast<CommunicationStatusNotification, UINotification>(factory.createCommand(command.getFrameBytes()));

            BOOST_CHECK( commandFromVec->getState() == command.getState());
            BOOST_CHECK( commandFromVec->getProcessNumber() == command.getProcessNumber());
            BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
            BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
            BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
            BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
            BOOST_CHECK( commandFromVec->getName() == command.getName());
    }

    BOOST_AUTO_TEST_CASE( receivingDataNotification )
    {
            UINotificationFactory factory;
            const vector<uint8_t> temp(9,9);
            ReceivingDataNotification command(temp);
            command.getFrameBytes();

            auto commandFromVec = static_pointer_cast<ReceivingDataNotification, UINotification>(factory.createCommand(command.getFrameBytes()));

            BOOST_CHECK( commandFromVec->getData() == command.getData());
            BOOST_CHECK( commandFromVec->getFrameBytes() == command.getFrameBytes());
            BOOST_CHECK( commandFromVec->getCommandType() == command.getCommandType());
            BOOST_CHECK( commandFromVec->getSystemVersion() == 1);
            BOOST_CHECK( commandFromVec->getDataSize() == command.getDataSize());
            BOOST_CHECK( commandFromVec->getName() == command.getName());
    }
BOOST_AUTO_TEST_SUITE_END()