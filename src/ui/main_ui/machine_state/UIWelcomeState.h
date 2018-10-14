#ifndef AHRS_UIWELCAMESTATE_H
#define AHRS_UIWELCAMESTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class UIWelcomeState final : public UIAbstractState
    {
    public:
        UIWelcomeState();
        ~UIWelcomeState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
        void setInformationPage(UIApplicationManager &uiApplicationManager);
    };
}

#endif