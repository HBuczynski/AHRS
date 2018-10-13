#ifndef AHRS_BITSOKSTATE_H
#define AHRS_BITSOKSTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class BitsOKState final : public UIAbstractState
    {
    public:
        BitsOKState();
        ~BitsOKState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
    };
}

#endif