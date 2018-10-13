#ifndef AHRS_UIABSTRACTSTATE_H
#define AHRS_UIABSTRACTSTATE_H

#include <string>
#include <logger/Logger.h>
#include "../../../system_states/UIMainStates.h"

namespace main_process
{
    class UIApplicationManager;
    
    class UIAbstractState
    {
    public:
        UIAbstractState(std::string name, UIMainStateCode stateCode);
        virtual ~UIAbstractState();

        virtual void setWelcomePage(UIApplicationManager &uiApplicationManager) = 0;
        virtual void communicationInProgress(UIApplicationManager &uiApplicationManager) = 0;

        const UIMainStateCode& getStateCode() const;
        const std::string& getName() const;

    protected:
        void setState(UIApplicationManager *machine, UIAbstractState *state);

        UIMainStateCode stateCode_;
        const std::string name_;
        utility::Logger& logger_;
    };
}

#endif //AHRS_UIABSTRACTSTATE_H
