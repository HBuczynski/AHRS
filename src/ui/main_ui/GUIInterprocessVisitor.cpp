#include "GUIInterprocessVisitor.h"

using namespace std;
using namespace main_process;
using namespace communication;

GUIInterprocessVisitor::GUIInterprocessVisitor(UIApplicationManager *uiApplicationManager)
    : uiApplicationManager_(uiApplicationManager)
{}

GUIInterprocessVisitor::~GUIInterprocessVisitor()
{}

void GUIInterprocessVisitor::visit(GUIPlaneResponse &data)
{

}
