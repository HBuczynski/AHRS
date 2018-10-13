#ifndef AHRS_PAGECONTROLLER_H
#define AHRS_PAGECONTROLLER_H

#include <QObject>

namespace gui
{
    class PageController : public QObject
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
        virtual void setExitPage() = 0;
        virtual void setLogsPage() = 0;
        virtual void setMenuPage() = 0;
        virtual void setConnectingPage() = 0;
        virtual void setInformationPageConnectionOK() = 0;
        virtual void setInformationPageBitOK() = 0;
        virtual void setInformationPageBitFalse() = 0;
    };
}

#endif
