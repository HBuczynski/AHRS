#ifndef AHRS_GUI_DATA_MANAGER_H
#define AHRS_GUI_DATA_MANAGER_H

#include <QObject>
#include <vector>
#include <atomic>

#include <interfaces/wireless_responses/CalibratingStatusResponse.h>

namespace gui
{
    struct BitsInformation
    {
        uint8_t master;
        uint8_t redundant;
        uint8_t masterBITS;
        uint8_t redundantBITS;
    };

    class GUIDataManager
    {
    public:
        GUIDataManager();

        void setBitsInformation(const BitsInformation& bitsInformation) noexcept;
        const BitsInformation& getBitsInformation() const noexcept;

        void setPlaneName(const std::string& name) noexcept;
        const std::string& getPlaneName() const noexcept;

        void setPlaneDataset(const std::string& planeDataset) noexcept;
        const std::string& getPlaneDataset() const noexcept;

        void setMainCallibrationParameters(const communication::CalibrationConfiguration& paramteres) noexcept;
        void setRedundantCallibrationParameters(const communication::CalibrationConfiguration& paramteres) noexcept;

        const communication::CalibrationConfiguration& getMainCallibrationParameters() const noexcept;
        const communication::CalibrationConfiguration& getRedundantCallibrationParameters() const noexcept;

        void setSystemActivation() noexcept;
        bool isSystemAcitve() noexcept;


    private:
        BitsInformation bitsInformation_;

        std::atomic<bool> isAHRSActive_;

        communication::CalibrationConfiguration masterCallibrationConfiguration_;
        communication::CalibrationConfiguration redundantCallibrationConfiguration_;

        std::string planeName_;
        std::string planeDataset_;
    };
}

#endif
