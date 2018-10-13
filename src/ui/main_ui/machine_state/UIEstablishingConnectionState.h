#ifndef AHRS_UIESTABLISHINGCONNECTIONSTATE_H
#define AHRS_UIESTABLISHINGCONNECTIONSTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class UIEstablishingConnectionState final : public UIAbstractState
    {
    public:
        UIEstablishingConnectionState();
        ~UIEstablishingConnectionState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
    };
}

#endif
