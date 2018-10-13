#include "BitsOKState.h"

#include "../UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;

BitsOKState::BitsOKState()
        :  UIAbstractState("BitsOKState", UIMainStateCode::BITS_OK)
{}

BitsOKState::~BitsOKState()
{}

void BitsOKState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void BitsOKState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}