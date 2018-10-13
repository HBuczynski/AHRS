#include "CommunicationOKState.h"

#include "../UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;

CommunicationOKState::CommunicationOKState()
        :  UIAbstractState("CommunicationOKState", UIMainStateCode::COMMUNICATION_OK)
{}

CommunicationOKState::~CommunicationOKState()
{}

void CommunicationOKState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void CommunicationOKState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}