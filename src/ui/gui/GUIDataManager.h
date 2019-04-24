#ifndef AHRS_GUI_DATA_MANAGER_H
#define AHRS_GUI_DATA_MANAGER_H

#include <QObject>
#include <vector>

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

        void setSystemActivation();
        bool isSystemAcitve();

    private:
        BitsInformation bitsInformation_;

        bool isAHRSActive_;

        std::string planeName_;
        std::string planeDataset_;
    };
}

#endif
