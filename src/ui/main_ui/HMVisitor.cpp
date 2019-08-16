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

void HMVisitor::initialize()
{
    faultManagement_.initialize();
}

void HMVisitor::visit(const HMErrorCommand& command)
{

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN-HMVisitor:: Received - HMErrorCommand: ") + to_string(static_cast<int>(command.getHMError()))
                                + " mode: " + to_string(static_cast<int>(command.getMode()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    HMErrorCommand newCom(command.getHMNode(), command.getHMError(), command.getMode(), uiApplicationManager_->getCurrentStateName());
    faultManagement_.handeError(newCom);
}

void HMVisitor::visit(const communication::HMInvalidConnectionCommand& command)
{
    faultManagement_.handleInvalidConnection(command.getProcessNumber());
}
