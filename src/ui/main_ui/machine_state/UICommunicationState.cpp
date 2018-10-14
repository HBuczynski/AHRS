#include "UICommunicationState.h"

#include "../UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;

UICommunicationState::UICommunicationState()
        :  UIAbstractState("UICommunicationState", UIMainStateCode::COMMUNICATION_OK)
{}

UICommunicationState::~UICommunicationState()
{}

void UICommunicationState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void UICommunicationState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}

void UICommunicationState::setInformationPage(UIApplicationManager &uiApplicationManager)
{

}
