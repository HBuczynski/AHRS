#ifndef AHRS_BITSFALSESTATE_H
#define AHRS_BITSFALSESTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class UIBitsFalseState final : public UIAbstractState
    {
    public:
        UIBitsFalseState();
        ~UIBitsFalseState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
        void setInformationPage(UIApplicationManager &uiApplicationManager);
    };
}

#endif