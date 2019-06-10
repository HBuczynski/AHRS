#include "HMFeederVisitor.h"
#include "ApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;
using namespace communication;

HMFeederVisitor::HMFeederVisitor(ApplicationManager *applicationManager)
    : applicationManager_(applicationManager),
      logger_(Logger::getInstance())
{}

HMFeederVisitor::~HMFeederVisitor()
{}

void HMFeederVisitor::visit(const HMErrorCommand& command)
{

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- HMFeederVisitor:: Received - HMErrorCommand, node: ") + to_string(static_cast<int>(command.getHMNode()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
