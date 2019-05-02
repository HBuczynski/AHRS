#ifndef AHRS_CALIBRATINGSTATUSRESPONSE_H
#define AHRS_CALIBRATINGSTATUSRESPONSE_H

#include "Response.h"

namespace communication
{
    enum CalibrationStatus : uint8_t
    {
        CALIB_PASSED = 0x01,
        CALIB_FAILED = 0x02,
        START_CALIBARTION = 0x03,
        IS_NOT_CALIBRATED = 0x04,
        CALIB_IN_THE_PROCESS = 0x05,
        IS_CALIBRATED = 0x06
    };

    struct CalibrationConfiguration
    {
        uint8_t progress = 0;
        CalibrationStatus status = IS_NOT_CALIBRATED;

        struct
        {
            float minX, maxX;
            float minY, maxY;
            float minZ, maxZ;
            uint8_t axis;
            uint8_t mode;
        } accelerometer;

        struct
        {
            float minX, maxX;
            float minY, maxY;
            float minZ, maxZ;
        } magnetometer;

        struct
        {
            uint16_t quadrant_11;
            uint16_t quadrant_12;
            uint16_t quadrant_13;
            uint16_t quadrant_21;
            uint16_t quadrant_22;
            uint16_t quadrant_23;
            uint16_t quadrant_31;
            uint16_t quadrant_32;
            uint16_t quadrant_33;

            uint8_t mode;
        }   ellipsoid;
    };

    class CalibratingStatusResponse final : public Response
    {
    public:
        CalibratingStatusResponse(CalibrationConfiguration configuration, uint8_t mode);
        ~CalibratingStatusResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        CalibrationConfiguration getCalibrationConfiguration() const;
        void setCalibrationConfiguration(const CalibrationConfiguration &status);

        uint8_t getMode() const noexcept;
        void setMode(uint8_t mode) noexcept;

    private:
        virtual void initializeDataSize() override;

        uint8_t mode_;
        CalibrationConfiguration calibrationConfiguration_;
    };
}

#endif
