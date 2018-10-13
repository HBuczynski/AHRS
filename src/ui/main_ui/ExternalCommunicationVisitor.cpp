#include "ExternalCommunicationVisitor.h"
#include "UIApplicationManager.h"

using namespace std;
using namespace main_process;
using namespace communication;

ExternalCommunicationVisitor::ExternalCommunicationVisitor(UIApplicationManager *uiApplicationManager)
    : uiApplicationManager_(uiApplicationManager)
{

}

ExternalCommunicationVisitor::~ExternalCommunicationVisitor()
{

}

void ExternalCommunicationVisitor::visit(ReceivingDataNotification& command)
{

}

void ExternalCommunicationVisitor::visit(CommunicationStatusNotification& command)
{

}
