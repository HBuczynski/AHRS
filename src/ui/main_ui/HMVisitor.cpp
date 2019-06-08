#include "HMVisitor.h"
#include "UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;
using namespace communication;

HMVisitor::HMVisitor(UIApplicationManager *uiApplicationManager)
    : uiApplicationManager_(uiApplicationManager),
      logger_(Logger::getInstance())
{}

HMVisitor::~HMVisitor()
{}

void HMVisitor::visit(const HMErrorCommand& command)
{

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN-HMVisitor:: Received - HMErrorCommand");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
