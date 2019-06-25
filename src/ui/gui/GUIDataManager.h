#ifndef AHRS_GUI_DATA_MANAGER_H
#define AHRS_GUI_DATA_MANAGER_H

#include <QObject>
#include <vector>
#include <atomic>

#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <interfaces/wireless_responses/BITsResponse.h>

namespace gui
{
    class GUIDataManager
    {
    public:
        GUIDataManager();

        void setMainBitsInformation(const communication::BitsInformation& bitsInformation) noexcept;
        const communication::BitsInformation& getMainBitsInformation() const noexcept;

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

        void setBITSActivation() noexcept;
        bool areBITSActive() noexcept;

        bool getIsMasterCalibrated() const;
        void setIsMasterCalibrated(bool isMasterCalibrated);

        communication::BitsInformation getRedundantBitsInformation() const;
        void setRedundantBitsInformation(const communication::BitsInformation &redundantBitsInformation);

    private:
        communication::BitsInformation mainBitsInformation_;
        communication::BitsInformation redundantBitsInformation_;

        std::atomic<bool> isAHRSActive_;
        std::atomic<bool> areBITSActive_;

        std::atomic<bool> isMasterCalibrated_;

        communication::CalibrationConfiguration masterCallibrationConfiguration_;
        communication::CalibrationConfiguration redundantCallibrationConfiguration_;

        std::string planeName_;
        std::string planeDataset_;
    };
}

#endif
