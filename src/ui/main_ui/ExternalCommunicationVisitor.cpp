#include "ExternalCommunicationVisitor.h"
#include "UIApplicationManager.h"

#include "machine_state/UICommunicationState.h"

using namespace std;
using namespace main_process;
using namespace communication;

ExternalCommunicationVisitor::ExternalCommunicationVisitor(UIApplicationManager *uiApplicationManager)
    :   informationParameters_(42,42,42),
        uiApplicationManager_(uiApplicationManager)

{}

ExternalCommunicationVisitor::~ExternalCommunicationVisitor()
{}

void ExternalCommunicationVisitor::visit(ReceivingDataNotification& command)
{

}

void ExternalCommunicationVisitor::visit(CommunicationStatusNotification& command)
{
    const auto status = command.getState();

    switch(status)
    {
        case UIExternalStateCode::MASTER :
            get<0>(informationParameters_) = 1;
            //uiApplicationManager_->setInformationPage(get<0>(informationParameters_), get<1>(informationParameters_), get<2>(informationParameters_));
            uiApplicationManager_->setInformationPage(get<0>(informationParameters_), 1, 0);

            uiApplicationManager_->setNewState( new UICommunicationState);
    }
}
