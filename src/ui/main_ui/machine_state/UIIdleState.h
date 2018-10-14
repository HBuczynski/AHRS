#ifndef AHRS_UIIDLESTATE_H
#define AHRS_UIIDLESTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class UIIdleState final : public UIAbstractState
    {
    public:
        UIIdleState();
        ~UIIdleState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
        void setInformationPage(UIApplicationManager &uiApplicationManager);
    };
}

#endif
