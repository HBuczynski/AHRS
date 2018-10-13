#ifndef AHRS_BITSFALSESTATE_H
#define AHRS_BITSFALSESTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class BitsFalseState final : public UIAbstractState
    {
    public:
        BitsFalseState();
        ~BitsFalseState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
    };
}

#endif