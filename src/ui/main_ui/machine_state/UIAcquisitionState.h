#ifndef AHRS_COMMUNICATIONOKSTATE_H
#define AHRS_COMMUNICATIONOKSTATE_H

#include "UIAbstractState.h"

namespace main_process
{
    class UIAcquisitionState final : public UIAbstractState
    {
    public:
        UIAcquisitionState();
        ~UIAcquisitionState();

        void setWelcomePage(UIApplicationManager &uiApplicationManager);
        void communicationInProgress(UIApplicationManager &uiApplicationManager);
        void setInformationPage(UIApplicationManager &uiApplicationManager);
    };
}

#endif