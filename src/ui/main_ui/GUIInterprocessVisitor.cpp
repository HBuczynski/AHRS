#include "GUIInterprocessVisitor.h"

using namespace std;
using namespace utility;
using namespace main_process;
using namespace communication;

GUIInterprocessVisitor::GUIInterprocessVisitor(UIApplicationManager *uiApplicationManager)
    : uiApplicationManager_(uiApplicationManager),
      logger_(Logger::getInstance())
{}

GUIInterprocessVisitor::~GUIInterprocessVisitor()
{}

void GUIInterprocessVisitor::visit(GUIPlaneResponse &data)
{

}

void GUIInterprocessVisitor::visit(communication::GUIWindowResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("GUIInterprocessVisitor:: Received - ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
