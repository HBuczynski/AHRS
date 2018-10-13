#ifndef AHRS_UIWELCAMESTATE_H
#define AHRS_UIWELCAMESTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class UIWelcameState final : public UIAbstractState
    {
    public:
        UIWelcameState();
        ~UIWelcameState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
    };
}

#endif