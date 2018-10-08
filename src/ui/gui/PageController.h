#ifndef AHRS_PAGECONTROLLER_H
#define AHRS_PAGECONTROLLER_H

namespace gui
{
    class PageController
    {
    public:
        PageController() {};
        virtual ~PageController() {};

        virtual void backToPreviousPage() = 0;

        virtual void setWelcomePage() = 0;
        virtual void setAHRSPage() = 0;
        virtual void setSystemSetupPage() = 0;
        virtual void setCallibrationSettingPage() = 0;
        virtual void setRestartPage() = 0;
    };
}

#endif
