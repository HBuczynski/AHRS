#include "BitsFalseState.h"

#include "../UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;

BitsFalseState::BitsFalseState()
        :  UIAbstractState("BitsFalseState", UIMainStateCode::BITS_FALSE)
{}

BitsFalseState::~BitsFalseState()
{}

void BitsFalseState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void BitsFalseState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}