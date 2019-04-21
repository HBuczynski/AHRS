#ifndef AHRS_PAGECONTROLLER_H
#define AHRS_PAGECONTROLLER_H

#include <QObject>
#include <vector>

namespace gui
{
    class PageController : public QObject
    {
    public:
        PageController() {};
        virtual ~PageController() {};

        virtual void backToPreviousPage() = 0;
        virtual void sendToMainProcess(std::vector<uint8_t> msg) = 0;

        virtual void setWelcomePage() = 0;
        virtual void setAHRSPage() = 0;
        virtual void setSystemSetupPage() = 0;
        virtual void setPlaneSettingPage() = 0;
        virtual void setRestartPage() = 0;
        virtual void setExitPage() = 0;
        virtual void setLogsPage() = 0;
        virtual void setMenuPage() = 0;
        virtual void setConnectingPage() = 0;
        virtual void setCallibrationPage() = 0;
        virtual void setInformationPage(uint8_t master, uint8_t redundant, uint8_t masterBITs, uint8_t redundantBITs) = 0;

        virtual void setPlaneName(const std::string& name) = 0;
        virtual const std::string& getPlaneName() = 0;

        virtual void setPlaneDataset(const std::string& name) = 0;
        virtual const std::string& getPlaneDataset() = 0;

        virtual void setBitsInformation(uint8_t master, uint8_t redundant, uint8_t masterBITs, uint8_t redundantBITs) = 0;
        virtual std::tuple<uint8_t , uint8_t , uint8_t, uint8_t> getBitsInformation() = 0;
    };
}

#endif
