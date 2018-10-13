#ifndef AHRS_COMMUNICATIONOKSTATE_H
#define AHRS_COMMUNICATIONOKSTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class CommunicationOKState final : public UIAbstractState
    {
    public:
        CommunicationOKState();
        ~CommunicationOKState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
    };
}

#endif