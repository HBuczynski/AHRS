#ifndef AHRS_BITSOKSTATE_H
#define AHRS_BITSOKSTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class UIBitsOKState final : public UIAbstractState
    {
    public:
        UIBitsOKState();
        ~UIBitsOKState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
        void setInformationPage(UIApplicationManager &uiApplicationManager);
    };
}

#endif