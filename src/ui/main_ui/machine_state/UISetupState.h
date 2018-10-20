#ifndef AHRS_UIESTABLISHINGCONNECTIONSTATE_H
#define AHRS_UIESTABLISHINGCONNECTIONSTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class UISetupState final : public UIAbstractState
    {
    public:
        UISetupState();
        ~UISetupState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
        void setInformationPage(UIApplicationManager &uiApplicationManager);
    };
}

#endif
