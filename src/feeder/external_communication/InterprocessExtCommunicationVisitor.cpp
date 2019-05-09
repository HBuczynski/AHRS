#include "InterprocessExtCommunicationVisitor.h"

using namespace std;
using namespace utility;
using namespace communication;

InterprocessExtCommunicationVisitor::InterprocessExtCommunicationVisitor()
    : logger_(Logger::getInstance())
{}

InterprocessExtCommunicationVisitor::~InterprocessExtCommunicationVisitor()
{}

void InterprocessExtCommunicationVisitor::visit(const CalibrateMgnDemandCommand &command)
{

}

void InterprocessExtCommunicationVisitor::visit(const communication::FeederWirelessWrapperCommand& command)
{

}

void InterprocessExtCommunicationVisitor::visit(const CalibrationStatusNotification& notification)
{

}

void InterprocessExtCommunicationVisitor::visit(const StateNotification &notification)
{

}

void InterprocessExtCommunicationVisitor::visit(const DbHashNotification& notification)
{

}

void InterprocessExtCommunicationVisitor::initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager)
{
    clientUDPManager_ = clientUDPManager;
}
