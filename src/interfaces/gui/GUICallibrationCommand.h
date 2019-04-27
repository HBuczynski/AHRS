#ifndef AHRS_GUICALIBRATIONCOMMAND_H
#define AHRS_GUICALIBRATIONCOMMAND_H

#include "GUICommand.h"
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>

namespace communication
{

    class GUICallibrationCommand final : public GUICommand
    {
    public:
        GUICallibrationCommand(CallibrationConfiguration configuration, uint8_t mode);
        ~GUICallibrationCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUICommandVisitor &visitor) override;

        CallibrationConfiguration getCalibrationConfiguration() const;
        void setCalibrationConfiguration(const CallibrationConfiguration &status);

        uint8_t getMode() const noexcept;
        void setMode(uint8_t mode) noexcept;

    private:
        virtual void initializeDataSize() override;

        uint8_t mode_;
        CallibrationConfiguration calibrationConfiguration_;
    };
}

#endif
