#include "ExternalCommunicationVisitor.h"

using namespace std;
using namespace main_process;
using namespace utility;
using namespace communication;

ExternalCommunicationVisitor::ExternalCommunicationVisitor()
    : logger_(Logger::getInstance())
{}

ExternalCommunicationVisitor::~ExternalCommunicationVisitor()
{}

void ExternalCommunicationVisitor::visit(const CalibrateMgnDemandCommand &command)
{

}

void ExternalCommunicationVisitor::visit(const CalibrationStatusNotification &command)
{

}
