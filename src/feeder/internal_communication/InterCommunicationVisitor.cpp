#include "InterCommunicationVisitor.h"
#include "InterManager.h"

#include <interfaces/ethernet_feeder/EthChangeStateCommand.h>

using namespace std;
using namespace communication;

InterCommunicationVisitor::InterCommunicationVisitor()
{}

InterCommunicationVisitor::~InterCommunicationVisitor()
{}

void InterCommunicationVisitor::initializeCurrentClient(InterManager *manager)
{
    interManager_ = manager;
}

void InterCommunicationVisitor::visit(const CalibrateMgnDemandCommand& command)
{}

void InterCommunicationVisitor::visit(const FeederWirelessWrapperCommand& command)
{}

void InterCommunicationVisitor::visit(const FeederCodeDemandCommand& command)
{
    auto changeCommand = make_unique<EthChangeStateCommand>(command.getStateCode());
    interManager_->sendCommands(move(changeCommand));
}
